%% T-Norm operators computation and plotting
% program implements and plots: (x) - strong conjunction, (+) - strong
% disjunction, ~ - negation, -> - implication/residuum, 
% <-> equivalency/biresiduum operators for minimum/Godel, product/Goguen, 
% Lukasiewicz, Yager (with parameter p) and (where possible) drastic T-Norms.
% input: T-Norm name: 'god' - Godel, 'gog' - Goguen, 'luk' - Lukasiewicz,
%                     'yag' - Yager, 'drast' - drastic
%        (Yager only): parameter p 
% output: plots of: (x) - strong conjunction, (+) - strong disjunction, 
% ~ - negation, -> - implication/residuum for input T-Norm based on 2D
% linspace

%% driver
function [] = tNormDriver(t_norm_name, varargin)
    % When working with Yager T-Norm check for input parameter p
    if(strcmp(t_norm_name, 'yag') == 1)
        num_args = length(varargin);
        if(num_args == 1)
            p = cell2mat(varargin);
        else
            disp('When working with Yager T-Norm you must enter the value of parameter p!');
            return;
        end
    else
        p = 0;
    end

    strongCon(t_norm_name, p); % (x) Strong Conjunction operator
    implication(t_norm_name, p); % -> Implication/Residuum operator 
    equivalence(t_norm_name, p); % <-> Equivalency/Biresiduum operator
    strongDis(t_norm_name, p); % (+) Strong Disjunction operator
    negation(t_norm_name, p); % ~ Negation operator
end

%% (x) Strong Conjunction operator
function strongCon(t_norm_name, p)
    x = linspace(0, 1);
    y = linspace(0, 1);
    [X, Y] = meshgrid(x, y);
    
    switch t_norm_name
        case 'god'
            Z = min(X, Y);
        case 'gog'
            Z = X .* Y;
        case 'luk'
            Z = max(0, X + Y - 1);
        case 'drast'
            Z = ((X == 1) > (Y == 1)) ~= ((Y == 1) > (X == 1)) .*X .*Y;             
        case 'yag'
            if p == 0
                strongCon('drast');
                return;
            elseif (p > 0 && p < inf)
                Z = max(0, 1 - ((1 - X).^p + (1 - Y).^p).^(1/p));
                % alt definition and equivalency check
                % Z2 = 1 - min(1, ((1 - X).^p + (1 - Y).^p).^(1/p));
                % Z_comp = (Z1 == Z2) == ones(size(Z1));
            else % p == inf
                strongCon('god');
                return;
            end
    end
    
    figure('Name', 'T-Norm Strong Conjunction 2D Contour');
    contour(X, Y, Z, 50);
    
    figure('Name', 'T-Norm Strong Conjunction 3D Mesh');
    mesh(X, Y, Z);
end

%% -> Implication/Residuum operator
function [] = implication(t_norm_name, p)
    x = linspace(0, 1);
    c = linspace(0, 1);
    [X, C] = meshgrid(x, c);
    R = zeros(size(X));
    
    switch t_norm_name
        case 'god'
            for i = 1:size(X, 1)
                for j = 1:size(C, 1)
                    if (X(i, j) > C(i, j))
                        R(i, j) = C(i, j);
                    else
                        R(i, j) = 1;
                    end
                end
            end
        case 'gog'
            for i = 1:size(X, 1)
                for j = 1:size(C, 1)
                    if (X(i, j) > C(i, j))
                        R(i, j) = C(i, j)/X(i, j);
                    else
                        R(i, j) = 1;
                    end
                end
            end
        case 'luk'
            for i = 1:size(X, 1)
                for j = 1:size(C, 1)
                    if (X(i, j) > C(i, j))
                        R(i, j) = 1 - X(i, j) + C(i, j);
                    else
                        R(i, j) = 1;
                    end
                end
            end
        case 'drast'
            for i = 1:size(X, 1)
                for j = 1:size(C, 1)
                    if (X(i, j) == 1)
                        R(i, j) = C(i, j);
                    else
                        R(i, j) = 1;
                    end
                end
            end
        case 'yag'
            if p == 0
                implication('drast');
                return;
            elseif (p > 0 && p < inf)
                for i = 1:size(X, 1)
                    for j = 1:size(C, 1)
                        if (X(i, j) > C(i, j))
                            R(i, j) = 1 - (max(0, (1 - C(i, j))^p - (1 - X(i, j))^p))^(1/p);
                        else
                            R(i, j) = 1;
                        end
                    end
                end
            else % p == inf
                implication('god');
                return;
            end
    end
    
    figure('Name', 'T-Norm Implication 2D Contour');
    contour(X, C, R, 50);
    
    figure('Name', 'T-Norm Implication 3D Mesh');
    mesh(X, C, R);
end

%% <-> Equivalency/Biresiduum operator
function [] = equivalence(t_norm_name, p)
    x = linspace(0, 1);
    y = linspace(0, 1);
    [X, Y] = meshgrid(x, y);
    
    switch t_norm_name
        case 'god'
            return;
        case 'gog'
            Z = 1./exp(abs(log(Y./X)));
        case 'luk'
            Z = 1 - abs(X - Y);
        case 'drast'
            return;
        case 'yag'
            if p == 0
                implication('drast');
                return;
            elseif (p > 0 && p < inf)
                Z = 1 - abs((1 - X).^p - (1 - Y).^p).^(1/p);
            else % p == inf
                strongCon('god');
                return;
            end
    end
    
    figure('Name', 'T-Norm Equivalence 2D Contour');
    contour(X, Y, Z, 50);
    
    figure('Name', 'T-Norm Equivalence 3D Mesh');
    mesh(X, Y, Z);
end

%% (+) Strong Disjunction operator
function [] = strongDis(t_norm_name, p)
    x = linspace(0, 1);
    y = linspace(0, 1);
    [X, Y] = meshgrid(x, y);
    
    switch t_norm_name
        case 'god'
            Z = max(X, Y);
        case 'gog'
            Z = X + Y - X .* Y;
        case 'luk'
            Z = min(1, X + Y);
        case 'drast'
            Z = ((X == 0) > (Y == 0)) ~= ((Y == 0) > (X == 0));
        case 'yag'
            if p == 0
                strongCon('drast');
                return;
            elseif (p > 0 && p < inf)
                Z = min(X.^p + Y.^p, 1);
            else % p == inf
                strongCon('god');
                return;
            end
    end
    
    figure('Name', 'T-Norm Strong Disjunction 2D Contour');
    contour(X, Y, Z, 50);
    
    figure('Name', 'T-Norm Strong Disjunction 3D Mesh');
    mesh(X, Y, Z);
end

%% ~ Negation operator
function [] = negation(t_norm_name, p)
    x = linspace(0, 1);
    
    switch t_norm_name
        case 'god'
            z = (x == 0);
        case 'gog'
            z = (x == 0);
        case 'luk'
            z = 1 - x;
        case 'drast'
            return;
        case 'yag'
            if p == 0
                implication('drast');
                return;
            elseif (p > 0 && p < inf)
                z = (1 - x.^p).^(1/p);
            else % p == inf
                strongCon('god');
                return;
            end
    end
    
    figure('Name', 'T-Norm Negation Plot');
    plot(x, z, '.');
end