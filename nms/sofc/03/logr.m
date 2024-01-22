clear; clc
A = csvread('binary.csv', 1, 0);
y = A(:,1); X = A(:, 2:4);
X = [ones(length(y),1) X];
[m, n] = size(X);
%logist rozdeleni
G = @(z) 1./(1 + exp(-z));
b = (X'*X)\(X'*y);
kmax = 1e3; k = 0 ; lambda = 1e-5; tol = 1e-10;
LL = @(Z) sum(y.*log(Z) + (1 - y).*log(1 - Z));
H = zeros(n); F = G(X*b); lnL = LL(F);
while 1
    f = F.*(1 - F);
    g = X'*(y.*(1 - F) - (1 - y).*F);
    for i = 1:n
        for j = i:n
            H(i,j) = -sum(f.*X(:,i).*X(:,j));
            if j ~= i
                H(j, i) = H(i, j);
            end
        end
    end
    kr = (H + lambda*eye(n))\g; bn = b - kr;
    Fn = G(X*bn); lnLn = LL(Fn);
    while lnLn < lnL
        kr = kr/2; bn = b - kr;
        Fn = G(X*bn); lnLn = LL(Fn);
    end
    if norm(bn - b) < tol || k > kmax
        break
    else
        lnL = lnLn; b = bn; F = Fn;
        k = k + 1;
    end
end

SE = sqrt(diag(inv(-H)));
zsc = b./SE;
pval = 2*(1 - normcdf(abs(zsc)));