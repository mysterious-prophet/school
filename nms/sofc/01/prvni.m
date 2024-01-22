 X = rand(150, 4);
 b = [0.6 -0.3 1.2 0.5];
 y = 0.45 + X.*b + 0.1*randn(150,1);
 y(100) = y(100) + 0.8;
% 
% X = [ones(150,1) X];
% b = (X'*X)^(-1)*(X'*y);
% 
% %pro dummy
% d = zeros(150,1);
% d(100) = 1;
% X = [X d];
% df = length(y) - size(X,2);
% pval = 2*(1 -tcdf(abs(tstat),df));


b = (X'*X)^(-1)*(X'*y);


T = length(y); 
k = size (X,2); 
e_roof = y - X*b;
s_sq = (e_roof'*e_roof)/(T - k);
var = s_sq * ((X'*X)^(-1));
std_err = diag(sqrt(var));

t_ratio = b./std_err;


p_value = 2*(1-tcdf(abs(t_ratio),T-k));
