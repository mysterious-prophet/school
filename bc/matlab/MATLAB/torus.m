% torus

clear; close all; clc;
R = 10; 
r = 5;
theta = 0:pi/20:2*pi;
phi = 0:pi/20:2*pi;

[PHI, THETA] = meshgrid(phi, theta);
X = (R+r*cos(PHI)).*cos(THETA);
Y = (R+r*cos(PHI)).*sin(THETA);
Z = r*sin(PHI);

brown = [0.2, 0, 0];
plot3(X,Y,Z, 'Color', brown);
hold on;
plot3(X,Y,Z, 'Color', brown);
axis equal;

figure
surf(X,Y,Z, -Z);
colormap autumn;
shading interp;
figure
mesh(X, Y, Z, -Z);

