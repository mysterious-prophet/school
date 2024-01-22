clear; clc
X = [1 1 0 0; 1 0 1 0]';
T = [0 1 1 0]';
X = [ones(4, 1) X];
% activation fction
F = @(z) 1./(1 + exp(-z));
% no of neurons
h = 2; o = 1; [m,n] = size(X);
W = 1 - 2*rand(n,h); v = 1 - 2*rand(h+1, o);
% old and new gradients
dW = zeros(size(W)); dv = zeros(size(v));
%step size, learning rate
alpha = 5; rho = 0.5;
% no of steps, precision
k = 0; kmax = 1e4; delta = 1e-4;

while 1 
    in2 = X*W;
    o2 = F(in2);
    in1 = [ones(m, 1) o2];
    o1 = F(in1*v);
    e = T - o1; sse = sum(sum(e'*e));
    d1 = o1.*(1 - o1).*e;
    D2 = (d1*v(2:end,:)').*o2.*(1 - o2);
    dv = rho*dv + alpha*in1'*d1;
    dW = rho*dW + alpha*X'*D2;
    W = W + dW; v = v + dv;
    if sse < delta || k > kmax
        return
    else
        k = k + 1;
    end
end