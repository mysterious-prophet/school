function [w, u] = generw(n)
u = randn(n, 1);
v = randn(n, 1);
u = 2*u -1;
v = 2*v -1;
w = u.^2 + v.^2;
end