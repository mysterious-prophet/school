close all;
clc;
clear variables;

%% define random problem
% sample size
% N = 100;
% n = 3;
% X = randn(N, n);
% X = [ones(N, 1), X];
% y = 0.53 + 0.12*randn(N, 1); % + 0.75*randn(N, 1) - 0.47*randn(N, 1);

%% read data
%filename = winequality-red.csv';
filename = 'Boston.csv';
X = table2array(readtable(filename, 'Range', 'B2:N507')); %A2:K1600
N = size(X, 1);
X = [ones(N, 1), X];
y = table2array(readtable(filename, 'Range', 'O2:O507')); %L2:L1600

%% solve linear regression coeffs
b = (X'*X)\(X'*y);

%% std error
% degrees of freedom
k = size(X, 2);
% differences
e = y - X*b;
% sum of differences squared, s^2, variance
rss = (e'*e);
s_sq = rss/(N-k);
var = s_sq .* (inv((X'*X)));
% std error
std_err = diag(sqrt(var));

%% t-stat
t_stat = b ./ std_err;

%% p-value
p_val = 2*(1-tcdf(abs(t_stat), N-1));

%% mean dependent var
mdv = sum(y) / N;

%% total sum of squares
tss = sum((y - mdv).^2);

%% R^2
r_sq = 1 - rss/tss;
adj_r_sq = 1 - (1 - r_sq)*((N - 1) / (N - k - 1));

%% std error of regression
std_err_reg = sqrt(rss/N);

%% log likelihood
log_like = -N/2*(log(2*pi) + log(rss/N)) - N/2;

%% f stat
f_stat = r_sq/(1 - r_sq) * (N - k - 1)/k;
f_stat_prob = fcdf(f_stat, k, N-k-1);

%% std deviation as dependent variable
std_dev_dv = sqrt(1/(N-1) * tss);

%% info crits
akaike_ic = 2*k - 2*log_like;
schwartz_ic = k*log(N) - 2*log_like;
hannan_quinn_ic = -2*log_like + 2*k*log(log(N));

%% durbin-watson stat
diffrs_sq = zeros(1, N);
for i = 2:1:N
    diffrs_sq(i) = (e(i) - e(i-1))^2;
end
durbin_watson_stat = sum(diffrs_sq)/rss;

%% print table
date = datetime('now');
fprintf("Dependent variable: y \n");
fprintf("Method: Least Squares \n");
fprintf("Date: %s \n", date);
fprintf("Sample: %i \n", N);
fprintf("--------------------------------------------------------------------------------- \n");
fprintf("Variable \t Coefficient \t Std. Error \t t-Statistic \t Prob. \n");
fprintf("--------------------------------------------------------------------------------- \n");
fprintf("C %21.6f %15.6f %15.6f %14.6f \n", ...
    b(1), std_err(1), t_stat(1), p_val(1));
for i=2:k
   fprintf("X(%i) %18.6f %15.6f %15.6f %14.6f \n", ...
       i-1, b(i), std_err(i), t_stat(i), p_val(i));
end
fprintf("--------------------------------------------------------------------------------- \n");
fprintf("R-squared %29.6f \t Mean dependent var %14.6f \n", ...
    r_sq, mdv);
fprintf("adjusted R-squared %20.6f \t S.D. dependent var %14.6f \n", ...
    adj_r_sq, std_dev_dv);
fprintf("S.E. of regression %20.6f \t Akaike criterion %14.4f \n", ...
    std_err_reg, akaike_ic);
fprintf("Sum squared resid %21.6f \t Schwartz criterion %12.4f \n", ...
    rss, schwartz_ic);
fprintf("Log-likelihood %24.6f \t Hannan-Quinn criter. %10.4f \n", ...
    log_like, hannan_quinn_ic);
fprintf("F-statistic %27.6f \t Durbin-Watson stat %14.6f \n", ...
    f_stat, durbin_watson_stat);
fprintf("Prob(F-statistic) %21.6f \n", ...
    f_stat_prob);
fprintf("--------------------------------------------------------------------------------- \n");

