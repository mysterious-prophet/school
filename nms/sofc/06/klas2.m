clear; clc; close all
load cereal.mat
D = cereal; [m,n] = size(D);
nc = floor(sqrt(m)); nr = ceil(m/nc);
theta = 0:2*pi/n:2*pi; theta(end) = [];
D = 1 + D - min(min(D));
for i = 1:m
    [x, y] = pol2cart(theta, D(i, :));
    X = [0*x; x]; Y = [0*y; y];
    x = [x x(1)]; y = [y y(1)];
    subplot(nr, nc, i);
    plot(X', Y'); 
    hold on
    plot(x, y);
    hold off
    title(labs(i));
    axis off
end