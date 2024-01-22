clear; clc; close all

D = load('Chwirut1.txt');
y_obs = D(:,1); x_obs = D(:,2);

% https://www.itl.nist.gov/div898/strd/nls/data/LINKS/DATA/Chwirut1.dat
%           Starting values                  Certified Values
% 
%         Start 1     Start 2           Parameter     Standard Deviation
%   b1 =   0.1         0.15          1.9027818370E-01  2.1938557035E-02
%   b2 =   0.01        0.008         6.1314004477E-03  3.4500025051E-04
%   b3 =   0.02        0.010         1.0530908399E-02  7.9281847748E-04
% 
% Residual Sum of Squares:                    2.3844771393E+03
% Residual Standard Deviation:                3.3616721320E+00
% Degrees of Freedom:                               211
% Number of Observations:                           214

start_vals = [0.1  0.01  0.02
              0.15 0.008 0.01];

% Jacobian
JJ = @(b)[x_obs.*(-exp(-b(1)*x_obs))./(b(2)+b(3)*x_obs) -exp(-b(1)*x_obs)./((b(2)+b(3)*x_obs).^2) x_obs.*(-exp(-b(1)*x_obs))./((b(2)+b(3)*x_obs).^2)];

b0 = start_vals(2,:)';
delta = 1e-15;
lambda = 1e-3;
while 1
    e = residuals(x_obs, y_obs, b0);
    J = JJ(b0);
    krok = (J'*J + lambda*eye(length(b0)))\(J'*e);
    b1 = b0 + krok; 
    sse0 = e'*e;
    e1 = residuals(x_obs, y_obs, b1);
    sse1 = e1'*e1;
    while sse1 > sse0
        krok = krok/2;
        b1 = b0 - krok; 
        e1 = residuals(x_obs, y_obs, b1);
        sse1 = e1'*e1;
    end
    if norm(b1 - b0) > delta
        b0 = b1;
        sse0 = sse1;
    else
        break
    end
end


%% Plots
% Observed data
figure(1)
plot(x_obs,y_obs,'*k')
xlabel('x')
ylabel('y')
hold on

% Regression
% Data is jumping all around the place => sort
[sorted_x_obs, sorted_y1] = sortData(x_obs, b1);
plot(sorted_x_obs, sorted_y1,'r', 'Linewidth', 1.25)
hold off

legend('observation', 'regression line')


%% SE, z-score, p-value
format long
b1
std_err = standardError(x_obs, y_obs, b1)
z_score = b1./std_err
p_value = 2*(1 - normcdf(abs(z_score)))
format short

figure(2)
hist(z_score)
xlabel('z-score')
ylabel('frequency')



%% Functions

function y = y_func(x, b)
y = exp(-b(1)*x)./(b(2)+b(3)*x);
end

function r = residuals(x, y, b)
r = y - y_func(x, b);
end

function [X, Y] = sortData(x, b)
y1 = y_func(x, b);
[X, i] = sort(x, 'descend');
Y = y1(i);
end

function std_err = standardError(x, y, b)
% Degrees of freedom
df = length(x) - length(b);
res = residuals(x, y, b);
ssq = sum(res.^2);
std_err = sqrt(ssq/df);
end
