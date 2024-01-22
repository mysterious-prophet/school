clear; clc; close all
f = @(x) 1-log(x).*exp(-x.^2);
a = 1;
b = 2;
x = a:0.01:b;
tol = 1e-8;
[fm, xm] = goldensecter(f, a, b, tol);
