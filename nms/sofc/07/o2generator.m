function o2 = o2generator(X, W, V)
    F = @(z) 1./(1 + exp(-z));
    m = size(X, 1);
    X = [ones(m,1) X];
    o1 = F(X*W);
    in2 = [ones(m,1) o1];
    o2 = F(in2*V);
end