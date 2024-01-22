clear; clc; close all
load iris_dataset
X = irisInputs'; T = irisTargets';
a = 0.6; b = 0.2;
[X1, T1, X2, T2, X3, T3] = dividedata2(X, T, a, b);
% [w, o] = RBFnet4class(X1, T1, 5);
kmin = 3; kmax = 32;
TPbest = 0;
d = @(x, c) sqrt(sum((x - c).^2, 2));
for i = kmin:kmax
    w = RBFnet4class(X1, T1, i);
    C = kmeanalgm(X2, i);
    C = sort(C);
    PHI = computePHI(X2, C, i);
    o = round(PHI * w);
    [TP, FP, TN, FN] = classevaluator(T2, o);
    if sum(TP) > TPbest
        TPbest = sum(TP);
        kbest = i;
    end
end