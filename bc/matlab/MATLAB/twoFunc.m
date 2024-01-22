clear; clc; close all
x = -3:0.01:3.5;
% f = @(x) x.^2-2.5;
% f1 = f(x);
f1 = x.^2 - 2.5;
f2 = 0.5*x.^3-2*x;

plot(x, f1, 'k-');
hold on;
plot(x, f2, 'k--');

xlabel('\it x');
ylabel('\it y');
title('Graf dvou funkci f1 a f2');
xlim([-2 3.5]);
ylim([-3.5 12]);

p = [0.5 -1 -2 2.5];
x0 = roots(p);
pr = x0.^2 - 2.5;

plot(x0, pr, 'o', 'Markersize', 5, 'MarkerEdgeColor', 'r', ...
    'MarkerFaceColor', 'w');


% legend('f1 = x^2 - 2.5', 'f2 = 0.5*x^3 - 2x', 'Location', 'NorthWestInside');
% xticks(-2:1:3.5);
% xtickslabels(1999:1:2003);

res = zeros(3,2);


annotation('arrow', [0.16 0.16], [0.42 0.36])
text(-1.9, 3, 'prusecik 1', 'fontsize', 13);

annotation('arrow', [0.55 0.55], [0.31 0.25])
text(0.5, 0.7, 'prusecik 2', 'fontsize', 13);

annotation('arrow', [0.80 0.80], [0.68 0.62])
text(2, 8, 'prusecik 3', 'fontsize', 13);
