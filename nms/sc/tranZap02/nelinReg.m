clear;
clc;
close all;

%% load data
data = load('gauss3.txt');
% https://www.itl.nist.gov/div898/strd/nls/data/gauss3.shtml
% Data:          1 Response  (y)
%                1 Predictor (x)
%                250 Observations
%                Average Level of Difficulty
%                Generated Data
% 
% Model:         Exponential Class
%                8 Parameters (b1 to b8)
% 
%                y = b1*exp( -b2*x ) + b3*exp( -(x-b4)**2 / b5**2 )
%                                    + b6*exp( -(x-b7)**2 / b8**2 ) + e
%  
%  
%           Starting values                  Certified Values
% 
%         Start 1     Start 2           Parameter     Standard Deviation
%   b1 =    94.9        96.0         9.8940368970E+01  5.3005192833E-01
%   b2 =     0.009       0.0096      1.0945879335E-02  1.2554058911E-04
%   b3 =    90.1        80.0         1.0069553078E+02  8.1256587317E-01
%   b4 =   113.0       110.0         1.1163619459E+02  3.5317859757E-01
%   b5 =    20.0        25.0         2.3300500029E+01  3.6584783023E-01
%   b6 =    73.8        74.0         7.3705031418E+01  1.2091239082E+00
%   b7 =   140.0       139.0         1.4776164251E+02  4.0488183351E-01
%   b8 =    20.0        25.0         1.9668221230E+01  3.7806634336E-01
% 
% Residual Sum of Squares:                    1.2444846360E+03  
% Residual Standard Deviation:                2.2677077625E+00
% Degrees of Freedom:                               242
% Number of Observations:                           250

y_obs = data(:, 1);
x_obs = data(:, 2);
start_vals = [94.9 0.009 90.1 113.0 20.0 73.8 140.0 20.0
    96.0 0.0096 80.0 110.0 25.0 74.0 139.0 22.0];
b0 = start_vals(2, :)';

%% lm regression
delta = 1e-6;
lambda = 1e-2;
while 1 
    e = residuals(x_obs, y_obs, b0);
    J = jacobian(x_obs, b0);
    step = (J'*J + lambda*eye(length(b0)))\(J'*e);
    b1 = b0 + step;
    sse0 = e'*e;
    e1 = residuals(x_obs, y_obs, b1);
    sse1 = e1'*e1;
    while sse1 > sse0
       step = step/2;
       b1 = b0 - step;
       e1 = residuals(x_obs, y_obs, b1);
       sse1 = e1'*e1;
    end
    if norm(b1-b0) < delta || abs(sse0-sse1) < delta
        break;
    else
        b0 = b1;
        sse0 = sse1;
    end
end
y_reg = y_func(x_obs, b1);

%% std. err., z-score, p-value
format long
std_err = stdErr(x_obs, y_obs, b1);
z_score = b1./std_err;
p_value = 2*(1 - normcdf(abs(z_score)));
format short

%% Plots
% Observed data
figure;
plot(x_obs, y_obs, '*k')
xlabel('x')
ylabel('y')
hold on

% Regression
plot(x_obs, y_reg, 'r', 'Linewidth', 1.25);
hold off

legend('Observed Data', 'Regression Line')

%% functions
% exponential function
function y = y_func(x, b)
y = b(1)*exp(-b(2)*x)+b(3)*exp(-(x-b(4)).^2/b(5).^2)+b(6)*exp(-(x-b(7)).^2/b(8).^2);
end

% gradient descent
function J = jacobian(x, b)
J = [exp(-b(2)*x) -b(1).*x.*exp(-b(2)*x) exp(-(x-b(4)).^2./b(5).^2) ...
    (2*b(3).*(x-b(4))./b(5).^2).*exp(-(x-b(4)).^2./b(5).^2) ...
    (2*b(3).*(x-b(4)).^2./b(5).^3).*exp(-(x-b(4)).^2./b(5).^2) ...
    exp(-(x-b(7)).^2./b(8).^2) ...
    (2*b(6).*(x-b(7))./b(8).^2).*exp(-(x-b(7)).^2./b(8).^2) ...
    (2*b(6).*(x-b(7)).^2./b(8).^3).*exp(-(x-b(7)).^2./b(8).^2)];
end

% residuals
function r = residuals(x, y, b)
r = y - y_func(x, b);
end

% std err
function std_err = stdErr(x, y, b)
df = length(x) - length(b);
res = residuals(x, y, b);
ssq = sum(res.^2);
std_err = sqrt(ssq/df);
end


