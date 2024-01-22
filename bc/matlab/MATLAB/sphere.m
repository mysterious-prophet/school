R = 10;
theta = 0:pi/20:2*pi;
phi = 0:pi/20:2*pi;

[THETA, PHI] = meshgrid(theta, phi);

X = R*cos(THETA).*cos(PHI);
Y = R*sin(THETA).*cos(PHI);
Z = R*sin(PHI);

plot3(X,Y,Z);
surf(X,Y,Z, -Z, 'EdgeColor', 'none');
colormap cool;
axis equal;