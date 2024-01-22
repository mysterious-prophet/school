clear; clc; close all
load iris_dataset
X = irisInputs'; T = irisTargets';
k = size(T, 2); % pocet trid
[m, n] = size(X);
Xi = range(X); Xm = min(X);
% nahodna teziste a clenstvi
C = repmat(Xi, k, 1).*unifrnd(eps, 1 - eps, k, n) + repmat(Xm, k, 1);
%Uo = unidrnd(1, k, m, 1);
Uo = randi([1, k], [m, 1]);
% vzdalenost
d = @(x, c) sqrt(sum((x - c).^2, 2));
q = 0;
while 1
    D = zeros(m, k);
    for i = 1:k
        Z = repmat(C(i, :), m, 1);
        D(:, i) = d(X, Z);
    end
    [~, Un] = min(D, [], 2);
    p = zeros(k, 1);
    for i = 1:k
        p(i) = sum(Un == i);
        if p(i) == 0
            C(i, :) = Xi.*unifrnd(eps, 1 - eps, 1, n) + Xm;
        else
            C(i, :) = sum(X(Un == i, :) / p(i));
        end
    end
    C = sort(C);
    err = sum((Un - Uo).^2);
    if err == 0 && all(p) || q >= 10000
        break
    else
        Uo = Un;
        q = q + 1;
    end
end

Unn = zeros(m, k);
for i = 1:k
    Unn(Un == i, i) = 1;
end
[TP, FP, TN, FN] = classevaluator(T, Unn);
