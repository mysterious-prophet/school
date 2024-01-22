close all
clear variables
clc

filename = 'heart.csv';
data = table2array(readtable(filename, 'Range', 'A2:N304'));
X = data(:, 1:end-1);
y = data(:, end);

X = [ones(length(y), 1) X];
[m, n] = size(X);
G = @(z) 1./ (1 + exp(-z));
b = (X'*X)\(X'*y); 
kmax = 1e3; k = 0; lambda = 1e-5; tol = 1e-10;
LL = @(Z) sum(y.*log(Z) + (1 - y).*log(1 - Z));
H = zeros(n);
F = G(X*b);
lnL = LL(F);
while 1
    f = F.*(1 - F);
    g = X'*(y.*(1 - F) - (1 - y).*F);
    for i = 1:n
        for j = i:n
            H(i, j) = -sum(f.*X(:, i).*X(:,j));
            if j ~= i
                H(j, i) = H(i, j);
            end
        end
    end
    kr = (H + lambda*eye(n))\g;
    bn = b - kr;
    Fn = G(X*bn);
    lnLn = LL(Fn);
    while lnLn < lnL
        kr = kr/2;
        bn = b - kr;
        Fn = G(X*bn);
        lnLn = LL(Fn);
    end
    if norm(bn - b) < tol || k > kmax
        break
    else
        lnL = lnLn;
        b = bn;
        F = Fn;
        k = k + 1;
    end
end
%% Statistiky
std_err = sqrt(diag(inv(-H)));
z_score = b./std_err;
p_value = 2*(1- normcdf(abs(z_score)));

%% Graf
figure(1)
% new = -5:0.01:5;
% plot(new, G(new),'r');
Xbn = X*bn;
xx = sort(Xbn, 'ascend');
plot(xx, G(xx), 'r-');
hold on

% Xbn_good = Xbn(abs(y-G(Xbn))<=0.2);
% Xbn_bad = Xbn(abs(y-G(Xbn))>0.2);
% y_good = y(abs(y-G(Xbn))<=0.2);
% y_bad = y(abs(y-G(Xbn))>0.2);
% scatter(Xbn_good, y_good, '*g')
% scatter(Xbn_bad, y_bad, '*b')
scatter(Xbn, y, '*k')
ylim([-0.1 1.1])
xlabel('t')
ylabel('y')
legend('f(t)', 'observations')






