function [X1, T1, X2, T2, X3, T3] = dividedata2(X, T, a, b)
    m = size(T, 1);
    p1 = round(a*m); p2 = round(b*m);
    q = randperm(m);
    X1 = X(q(1:p1), :); T1 = T(q(1:p1), :);
    X2 = X(q(p1+1:p1+p2), :); T2 = T(q(p1+1:p1+p2), :);
    X3 = X(q(p1+p2+1:end), :); T3 = T(q(p1+p2+1:end), :);
end