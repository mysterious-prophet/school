function [w, o] = RBFnet4class(X, T, k)
    % clear; clc; close all
    % load iris_dataset
    % X = irisInputs'; T = irisTargets';
    [m, n] = size(X);
    % k = size(T, 2); % pocet trid
    % d = @(x, c) sqrt(sum((x - c).^2, 2));
    % k = 8; 
    lambda = 1e-2;
    C = kmeanalgm(X, k);
    C = sort(C);
    PHI = computePHI(X, C, k);
    % for i = 1:k
    %     Z = repmat(C(i, :), m, 1);
    %     PHI(:, i) = d(X, Z);
    % end
    %PHI = [ones(m, 1) PHI];
    w = (PHI'*PHI + lambda*eye(k+1))\(PHI'*T);
    o = PHI*w;
    o = round(o);
end