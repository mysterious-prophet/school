function [x, q] = SORmethod(A, b, omega, tol)
n = length(b);
xold = zeros(n, 1);
xnew = xold;
q = 0;
while 1
    for i = 1:n
        xnew(i) = (1-omega)*xold(i) + omega/A(i,i) * ...
            (b(i) -A(i, i+1:n)*xold(i+1:n) - A(i, 1:i-1)* ...
            xnew(1:i-1));
    end
    if norm(xnew - xold) < tol
        break;
    end
    xold = xnew;
    q =  q+1;   
end
x = xnew;