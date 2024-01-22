f = @(x) exp(-x).*sin(10*x);
%f = @(x) exp(-x.^2/2)/sqrt(2*pi);
a = 0;
b = 2*pi;
tol = 1e-20;
I = rombergint(f, a, b, tol);