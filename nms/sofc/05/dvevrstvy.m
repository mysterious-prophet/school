%Matlab code for XOR problem
%predelat toto na funkci o poctu vrstev a X(podle me)
clear; clc
X = [1 1 1 1; 0 0 1 1; 0 1 0 1]';
T = [0 1 1 0]';
% D = randn(200,5);
% T = D(:,1);
% X =
%T = [0 1 1 0]'; 
alpha = 10; rho = 0.7;
X = [ones(4,1) X];
beta = 1;
F = @(z) 1./(1 + exp(-z));
h = 4; O = 1;
[m,n] = size(X);
W1 = beta*(1-2*rand(n,h));
W2 = beta*(1-2*rand(h+1,O));

dW1 = zeros(size(W1));
dW2 = zeros(size(W2));
k = 0; kmax = 1e4; delta = 1e-4; lambda = 1e-4;
while 1
   o1 = F(X*W1);
   in2 = [ones(m,1) o1];
   o2 = F(in2*W2);
   err = repmat(T,1,O) - o2;
   sse = sum(sum(err.*err));
   Po1 = o2.*(1 - o2);
   Po2 = zeros(m*O,h);
   for i  = 1:O
       Jo = repmat(Po1(:), 1, h+1).*repmat(in2,O,1);
       dW2(:,i) = rho*dW2(:,i) + alpha*(Jo'*Jo+lambda*eye(h+1))\(Jo'*err(:));
       Po2((1:m)+(i-1)*m,:) = repmat(Po1(:,i),1,h).*repmat(W2(2:end,i)',m,1);
   end
   Po3 = (o1.*(1-o1));
   for i = 1:h
       Po4 = repmat(Po3(:,i),O,1).*Po2(:,i);
       Jh = repmat(Po4,1,n).*repmat(X,O,1);
       dW1(:,i) = rho*dW1(:,i) + alpha*(Jh'*Jh+lambda*eye(n))\(Jh'*err(:));
   end
   
   
%    delta3 = (o3*(1-o3)).*err;
%    delta2 = (o2*(1-o2)).*(delta3*W3(2:end,:)');
%    delta1 = (o1*(1-o1)).*(delta2*W2(2:end,:)');
   %dW1 = rho*dW1 + alpha*X'*delta1;
   W1 = W1+dW1;
   %dW2 = rho*dW2 + alpha*in2'*delta2;
   W2 = W2+dW2;
   
%    e = T - o1; sse = e'*e;
%    d1 = o1.*(1 - o1).*e;
%    D2 = (d1*v(2:end)').*o2.*(1 - o2);
%    dv = rho*dv + alpha*in1'*d1;
%    dW = rho*dW + alpha*X'*D2;
%    W = W + dW; v = v + dv;
if sum(sum(sse)) < delta || k > kmax
    break
else
    k = k+1;
end
end
  