clear; clc; %https://en.wikipedia.org/wiki/Gauss%E2%80%93Seidel_method
n = 100;
A = randi([-5,5],n);
A = A'*A;
x0 = randi([-2, 1], [n,1]);
b = A*x0;

% A0 = [28 -6 2; 2 -30 4; 1 3 36];
% A = A0'*A0;
% b0 = [25 -10 -16]';
% b = A0'*b0;

% A=[15 -1 2; 2 -10 1; 1 3 18];
% b = [30 23 -22]';
% x0 = A\b;

% xold = zeros(n,1);


tol = 1e-5;
omega = 0.1:0.1:2;
qopt = inf;
for i = 1:length(omega)
    [x, q] = SORmethod(A, b, omega(i), tol);
    if q < qopt
        qopt = q;
        omegaopt =omega(i);
    end
end

[x0 x]


% while stop
%     for i = 1:n
%         xnew(i) = (1/(A(i,i))) * (b(i) - A(i, i+1:n)*xold(i+1:n) - ...
%             A(i , 1:i-1)*xnew(1:i-1)); 
%     end
%     if norm(xnew - xold) < tol
%         stop = 0;
%     end
%     xold = xnew;
%     q =  q+1;   
% end