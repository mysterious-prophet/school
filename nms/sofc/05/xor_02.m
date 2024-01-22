clear; clc; close all
D = randn(300, 5);
T = D(:, 1);
T1 = D(201:300, 1);
X = D(:, 2:end);
X1 = D(201:300, 2:end); X1 = [ones(100,1) X1];
X = [ones(length(T), 1) X];
alpha = 0.7; beta = 1; rho = 0.2;
F = @(x) 1./(1 + exp(-x));
[m, n] = size(X);
h = 40; o = 1;
%W = (X'*X)\(X'*T);
W = beta * (1 - 2*rand(n, h));
dW = zeros(size(W));
sse0 = inf;
delta = 1e-1; sse = 1; k = 0; kmax = 1e4;
while 1 
    o1 = F(X*W);
    in2 = [ones(m, 1) o1];
    w = (in2'*in2)\(in2'*T);
    o2 = in2*w;
    err = (T - o2);
    sse = err'*err;
    Delta = (o1.*(1 - o1)).*(err*w(2:end)');
    dW = rho * dW + alpha * X' * Delta;
    W = W + dW;
    if abs(sse - sse0) < delta || k > kmax
        break
    else
        k = k + 1;
        sse0 = sse;
    end
end
plot(T);
hold on
plot(o2, 'or');

o11 = f(X1*W);
in21 = [ones(100,1) o11];
o21 = in21*v;
plot((201:300)