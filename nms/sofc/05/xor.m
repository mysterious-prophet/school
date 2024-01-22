clear; clc
X = [1 1 1 1; 0 0 1 1; 0 1 0 1]';
T = [0 1 1 0]';
% activation fction
F = @(z) 1./(1 + exp(-z));
%step size learning rate, bias
alpha = 5; rho = 0.7; beta = 1;
% no of neurons
h1 = 4; h2 = 3; o = 2; [m,n] = size(X);
W1 = beta*(1 - 2*rand(n,h1));
W2 = beta*(1 - 2*rand(h1+1, h2));
W3 = beta*(1 - 2*rand(h2+1, o));
% old and new gradients
dW1 = zeros(size(W1));
dW2 = zeros(size(W2));
dW3 = zeros(size(W3));
% no of steps, precision
k = 0; kmax = 1e4; delta = 1e-4;

while 1 
    o1 = F(X*W1);
    in2 = [ones(m,1) o1];
    o2 = F(in2*W2);
    in3 = [ones(m,1) o2];
    o3 = F(in3*W3);
    err = repmat(T,1,o) - o3;
    sse = sum(sum(err.*err));
    delta3 = o3.*(1 - o3).*err;
    delta2 = (o2.*(1 - o2)).*(delta3*W3(2:end,:)');
    delta1 = (o1.*(1 - o1)).*(delta2*W2(2:end,:)');
    dW1 = rho * dW1 + alpha*X'*delta1;
    W1 = W1 + dW1;
    dW2 = rho * dW2 + alpha*in2'*delta2;
    W2 = W2 + dW2;
    dW3 = rho * dW3 + alpha*in3'*delta3;
    W3 = W3 + dW3;
    if sum(sum(sse)) < delta || k > kmax
        break
    else
        k = k + 1;
    end
end
    
%     in2 = X*W;
%     o2 = F(in2);
%     in1 = [ones(m, 1) o2];
%     o1 = F(in1*v);
%     e = T - o1; sse = sum(sum(e'*e));
%     d1 = o1.*(1 - o1).*e;
%     D2 = (d1*v(2:end,:)').*o2.*(1 - o2);
%     dv = rho*dv + alpha*in1'*d1;
%     dW = rho*dW + alpha*X'*D2;
%     W = W + dW; v = v + dv;
%     if sse < delta || k > kmax
%         return
%     else
%         k = k + 1;
%     end
% end