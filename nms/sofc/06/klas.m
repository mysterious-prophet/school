clear; clc; close all
load iris_dataset
% X = [setosa; versicolor; virginica];
% T = zeros(150, 3);
% T(1:50,1) = 1; T(51:100,2) = 1; T(101:150,3) = 1;
T = irisTargets';
X = irisInputs';
% plotmatrix(X);
f = @(z) [sin(z) cos(z) sin(2*z)];
theta = (-pi:pi/50:pi)'; m = length(theta);
F = f(theta); F = [1/sqrt(2)*ones(m,1) F];
xse = X((T(:,1)==1), :); n1 = size(xse, 1);
xve = X((T(:,2)==1), :); n2 = size(xve, 1);
xvi = X((T(:,3)==1), :); n3 = size(xvi, 1);
yse = xse*F';
yve = xve*F';
yvi = xvi*F';
h1 = plot(repmat(theta, 1, n1), yse', 'b-');
hold on
h2 = plot(repmat(theta, 1, n2), yve', 'm-');
h3 = plot(repmat(theta, 1, n3), yvi', 'g-');
hold off
legend([h1(1) h2(1) h3(1)], 'setosa', 'versicolor', 'virginica');
axis tight
xlabel('\theta');
ylabel('andrews f');