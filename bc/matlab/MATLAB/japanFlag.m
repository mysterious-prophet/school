clear; clc; close all

% Vx = [-1.5 1.5 1.5 -1.5 -1.5];
% Vy = [-1 -1 1 1 -1];
% hold on
% fill(Vx, Vy, 'w');
% 
% r = 3/5;
% theta = 0:pi/50:2*pi;
% x = r*cos(theta);
% y = r*sin(theta);
% fill(x, y, 'r');

Vxb = [-1.5 -1.5 0];
Vyb = [-1 1 0];
hold on

fill(Vxb, Vyb, 'b');

Vxr = [0 -1.5 1.5 1.5 0];
Vyr = [0 -1 -1 0 0];
fill(Vxr, Vyr, 'r');

Vxw = [0 -1.5 1.5 1.5 0];
Vyw = [0 1 1 0 0];
fill(Vxw, Vyw, 'w');

axis equal off;


