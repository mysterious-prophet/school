clear; clc; close all;

%% factorial
inp = input('input: ');
fac = factorial(inp);
if(size(fac, 1) > 0)
    format_spec = 'The factorial of %d is %d \n';
    fprintf(format_spec, inp, fac);
end

%% quadratic equation
a = 1; b = 4; c = -5;
% a = 1; b = -10; c = 25;
% a = 5; b = 4; c = 10;
result = quadSolver(a, b, c);
if(size(result, 1) > 0)
    format_spec = 'The solution of the quadratic equation (%.2fx^2) + (%.2fx) + (%.2f) = 0 is: ';
    fprintf(format_spec, a, b, c);
    disp(result);
end

%% matrices
m = 4;
A = rand(m, m);

sum_X = sum(sum(A));
max_X = max(max(A));
min_X = min(min(A));

b = rand(m, 1);
inv_A = inv(A);

% X = inv_A * b;
X = A \ b;

%% plotting
x = 0:pi/20:2*pi;
y1 = sin(x);
y2 = cos(x);
y3 = ones(1, size(x, 2));

fig = figure;
hold on
plot(x, y1, 'LineWidth', 3);
plot(x, y2, 'g--');
plot(x, y3, 'rx');
hold off
axis([0 2*pi -1.5 1.5]);
title('Exercise plot');
leg = legend('sin(x)', 'cos(x)', 'I(x)', 'Location', 'best');
title(leg, 'Legend');
xlabel('x');
ylabel('f(x)');

%% limit and derivative
[lim_x, der_f] = symbEx();

%% bubblesort
x = randi(1000, 1, 10);
disp('Unsorted vector x: ');
disp(x);
x_sort = bubbleSort(x);
disp('Sorted vector x: ');
disp(x_sort);