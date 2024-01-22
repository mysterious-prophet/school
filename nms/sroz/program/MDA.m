%% Multiple Linear Discriminant Analysis (Rao)
% program reduces input data into data with input reduced dimension
% input: reduced dimension size
%      : [input data filename .csv] else load iris dataset
%      : [target filename .csv] else load iris target
% output: transformed input data I
%       : transformation matrix W
%       : class separation coefficient S
% e.g.: MDA(2, 'iris_data.csv', 'iris_target.csv');
%     : MDA(2);

%% driver
% load data
% check input reduction dimension 
% perform MDA
function [I, W, S] = MDA(red_dim, varargin) % reduction dim, [input], [target]
    if(nargin < 1 || nargin == 2 || nargin > 3)
        disp('Incorrect number of input arguments (must be 1 or 3)! ');
        return;
    elseif(nargin == 1)
        [input, target] = loadIrisData();
    elseif(nargin == 3)
        input_filename = varargin{1};
        target_filename = varargin{2};
        [input, target] = loadInputData(input_filename, target_filename);
    end
    
    if(red_dim < 1 || red_dim > (size(input, 2) - 1))
        disp('Reduction must be into dimension greater or equal to 1 and smaller or equal to (N-1)!');
        return;
    else       
        [input, ~, num_classes, num_features, div_indices] = preprocessing(input, target);
        [class_feature_means, feature_means] = calculateMeans(input, div_indices, num_classes, num_features);
        [Sw, Sb] = calculateScatterMatrices(input, div_indices, class_feature_means, feature_means, num_classes, num_features);
        [eig_vectors, ~] = calculateEigVectsVals(Sw, Sb);
        [W, I, S] = transformData(input, Sw, Sb, eig_vectors, red_dim);
    end
end

%% load iris dataset
% load matlab fisher iris dataset
function [input, target] = loadIrisData()
%     input = [randn(10,4); randn(15,4) + 1.37; randn(7, 4) + 0.64]; 
%     target = [ones(10,1); 2*ones(15,1); 3*ones(7,1)];

    load fisheriris;
    input = meas;
    target = zeros(size(input, 1), 1);
    for i = 1:size(species)
       if(strcmp(species{i}, 'setosa'))
           target(i) = 1;
       elseif(strcmp(species{i}, 'versicolor'))
           target(i) = 2;
       elseif(strcmp(species{i}, 'virginica'))
           target(i) = 3;
       end
    end
end

%% load user input data
% load data and target from .csv files
function [input, target] = loadInputData(input_filename, target_filename)
    input = readmatrix(input_filename);
    target = readmatrix(target_filename);
end

%% preprocess data
% get number of classes, features, samples
% sort target and input
% find indices where ordered input changes from one class to another
function [input, target, num_classes, num_features, div_indices] = preprocessing(input, target)
    num_classes = length(unique(target));
    [num_samples, num_features] = size(input);
    [target, sort_indices] = sort(target, 'ascend');
    input = input(sort_indices,:);
    
    % find how the sample data is divided into classes (indices)
    div_indices = ones(num_classes+1, 1);
    div_indices(end) = num_samples+1;
    k = 2;
    for i = 1:num_samples-1
        if(target(i+1) ~= target(i))
            div_indices(k) = i+1;
            k = k + 1;
        end
        if(k == num_classes+1)
            break;
        end
    end
end

%% calculate means
% calculate means of features in classes and total mean of features
function [class_feature_means, feature_means] = calculateMeans(input, div_indices, num_classes, num_features)
    class_feature_means = zeros(num_classes, num_features);
    for i = 1:num_classes
        class_feature_means(i, :) = mean(input(div_indices(i):div_indices(i+1)-1, :), 1);
        for j = 1:num_features
            class_feature_means(i, j) = mean(input(div_indices(i):div_indices(i+1)-1, j));
        end
    end
    feature_means = mean(class_feature_means, 1);
end

%% calculate scatter matrices
% calculate within-class and between-class scatter matrices
function [Sw, Sb] = calculateScatterMatrices(input, div_indices, class_feature_means, feature_means, num_classes, num_features)
    Sw = zeros(num_features, num_features);
    Sb = zeros(num_features, num_features);    
    for i = 1:num_classes
        Sw_class = zeros(num_features, num_features);
        Sb_class = (div_indices(i+1) - div_indices(i)) * ... 
            (class_feature_means(i, :) - feature_means)' * ...
            (class_feature_means(i, :) - feature_means);
        for j = div_indices(i):div_indices(i+1)-1
            covar = input(j, :) - class_feature_means(i ,:);
            covar = covar' * covar;
            Sw_class = Sw_class + covar;
        end
        Sw = Sw + Sw_class;
        Sb = Sb + Sb_class;
    end
end

%% calculate eigen vectors and eigen values
% perform eigen decomposition
% sort eigen values and vectors in descending order
function [eig_vectors, eig_values] = calculateEigVectsVals(Sw, Sb)
    [eig_vectors, eig_values] = eig(Sb, Sw);
    eig_values = diag(eig_values);
    [eig_values, sort_indices] = sort(eig_values, 'descend');
    eig_vectors = eig_vectors(:, sort_indices);
end

%% transform input data
% transform input data into matrix of input size signifying dimension
% reduction
% calculate class separation coefficient
function [W, I, S] = transformData(input, Sw, Sb, eig_vectors, red_dim)
    W = eig_vectors(:, 1:red_dim);
    I = input * W;
    S = det(W' * Sb * W) / det(W' * Sw * W);
end