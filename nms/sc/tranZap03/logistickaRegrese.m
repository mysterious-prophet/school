close all
clear variables
clc

% Datovy soubory ktery zpracovavame se tyka prijimaciho procesu ke studia
% na americky univerzitach

% gpa - prospech
% gre - pocet bodu z testu
% rank - specialni uspechy/doporuceni

A = csvread('binary.csv', 1, 0);
y = A(:, 1);
X = A(:, 2:4);
X = [ones(length(y), 1) X];
[m, n] = size(X);
G = @(z) 1./ (1 + exp(-z)); % CDF logist rozdeleni

% \ operator according to MATLAB docs
%  x = A\B solves the system of linear equations A*x = B. The matrices A and B must have the same number of rows.
b = (X'*X)\(X'*y); 

% Nejvyssi pocet kroku
kmax = 1e3;
k = 0;
lambda = 1e-5;

% Tolerance
tol = 1e-10;

LL = @(Z) sum(y.*log(Z) + (1 - y).*log(1 - Z));

% Hessian alokace
H = zeros(n);

% Funkce velke F podle {log-prob-notes}
F = G(X*b);

% log likelihood?
lnL = LL(F);

% Konec pripravy, pry uz mame vsecko - ostatni uz zname


while 1
    % b je odhad ziskany metodou nejmensich ctvercu
    % musice spocitat prvni a druhou derivaci, Hessian, Gradient, to co
    %  jsme delali minule
    
    % Nejakou sumu neptrebujeme, muzeme to udelat vektorove
    % Hessian je (9) z {log-prob-notes}
    % (9) je gradient?
    
    % Potrebujeme maly f pro druhou derivaci (velke F uz mame)
    f = F.*(1 - F); % (8-2; {log-prob-notes})
    
    % Gradient z (9; {log-prob-notes})
    g = X'*(y.*(1 - F) - (1 - y).*F);
    
    % Vypocet hessianu
    for i = 1:n
        for j = i:n
            H(i, j) = -sum(f.*X(:, i).*X(:,j));
            if j ~= i
                H(j, i) = H(i, j);
            end
        end
    end
    
    % Muzeme spocitat krok
    kr = (H + lambda*eye(n))\g;
    bn = b - kr;
    
    % Musime spocitat kolik je F, kolik je log likelihood
    Fn = G(X*bn);
    lnLn = LL(Fn);
    
    % Tento cyklus je tady aby se nam vratil, kdyby krok byl moc dlouhy?
    while lnLn < lnL
        kr = kr/2;
        bn = b - kr;
        Fn = G(X*bn);
        lnLn = LL(Fn);
    end
    
    % Protoze mame vecny cyklus, musime nejak zastavit
    if norm(bn - b) < tol || k > kmax
        break
    else
        lnL = lnLn;
        b = bn;
        F = Fn;
        
        k = k + 1;
    end
end

% Jeste musime spocitat ty statistiky:
% Vime ze SE je neco
SE = sqrt(diag(inv(-H))); % Neco o Fisherove matice, ze musi byt s minusem?
% z-score
zsc = b./SE;
% p-value - musi byt vetsi ze 0.05? (01:08:30)
pval = 2*(1- normcdf(abs(zsc)));
% p-value vychazi docela male, takze ty --- jsou statisticky vyznamne od
% nuly (01:14:00)


% Tento skript implementuje cistou Newtonovu metodu (ne uplne cisty)
%  1. derivaci, 2. derivaci

% Nas 3. ukol: (01:07:00)
% 

%% Reference

% {log-prob-notes}: Logit and Probit Notes pdf