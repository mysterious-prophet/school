close all;
clear variables;
clc;

%% load data
filename = 'heart'; %'diabetes2.csv' 'heart.csv' 'candy-data.csv'
data = table2array(readtable(filename, 'Range', 'A2:N304')); % 'A2:I769' 'A2:N304' 'B2:M86'
% indx = [1 2 3 6 7];
%indx = [ 2 3 4 8 9 10 12 13];
indx = [2 3 4 8 9 10 12 13];
% indx = [ 2 8];
X = data(:, indx);
y = data(:, end);
X = [ones(length(y), 1) X];
[m, n] = size(X);

%% define logistic functions
G = @(z) 1./ (1 + exp(-z)); % logistic cdf
b = (X'*X)\(X'*y); % coeffs init
LL = @(Z) sum(y.*log(Z) + (1 - y).*log(1 - Z)); %log likelihood 
H = zeros(n); % hessian init
F = G(X*b); % init according to logit model
lnL = LL(F);

%% lm cycle
max_iters = 1e4;
iter = 0; 
lambda = 1e-5; % gradient step size
delta = 1e-15; % accuracy
while 1
    f = F.*(1-F); % first derivative of logistic cdf acc. to z
    g = X'*(y.*(1-F)-(1-y).*F); % first derivative of loglike acc. to b
    for i = 1:n
        for j = i:n
            H(i, j) = -sum(f.*X(:, i).*X(:, j)); % hessian of loglike acc. to bb
            if j ~= i
                H(j, i) = H(i, j); % is symmetrical 
            end
        end
    end
    % gradient descent
    step = (H + lambda*eye(n))\g;
    b_n = b - step;
    F_n = G(X*b_n);
    lnL_n = LL(F_n);
    while lnL_n < lnL %return
        step = step/2;
        b_n = b - step;
        F_n = G(X*b_n);
        lnL_n = LL(F_n);
    end
    % if achieved desired accuracy or too many iterations break
    if norm(b_n - b) < delta || iter > max_iters
        break
    else % next step
        lnL = lnL_n;
        b = b_n;
        F = F_n;
        iter = iter + 1;
    end
end

%% stats
std_err = sqrt(diag(inv(-H)));
z_score = b./std_err;
p_value = 2*(1 - normcdf(abs(z_score)));

%% plot
figure;
Xb_n = X*b_n;
x_sort = sort(Xb_n, 'ascend');
plot(x_sort, G(x_sort), 'b-');
hold on

% threshold
yline(0.5, 'k--');

% corr. and incorr. classifications
Xb_n_corr = Xb_n(abs(y-G(Xb_n))<=0.5);
Xb_n_incorr = Xb_n(abs(y-G(Xb_n))>0.5);
y_corr = y(abs(y-G(Xb_n))<=0.5);
y_incorr = y(abs(y-G(Xb_n))>0.5);
scatter(Xb_n_corr, y_corr, 'og')
scatter(Xb_n_incorr, y_incorr, 'or')

corr_size = size(Xb_n_corr, 1);
incorr_size = size(Xb_n, 1) - corr_size;

x_lab = xlabel('$ z = \beta_{0} + \displaystyle\sum_{i=1}^{n} \beta_{i}x_{i} $');
set(x_lab, 'Interpreter', 'latex');
ylabel('y')
leg = legend('$y = \frac{1}{1 + e^{-z}}$', 'Threshold', 'Corr. class.', 'Incorr. class.', 'Location', 'northwest');
set(leg ,'Interpreter','latex')


