%nelinearni regrese
clear; clc;
D = load('misrala.txt');
%nebo D=xlsread('misrala.xls', 'A1:B14']) kdyz je to xls soubor
y=D(:,1);
x=D(:,2);

f = @(b) y - b(1)*(1 - exp(-b(2)*x));
b0 = [500 1e-4]';

%gradient
g =  @(b) [-(1 - exp(-b(2)*x)), -b(1)*x.*exp(-b(2)*x)];
alpha = 1; S0 = sum(f(b0).^2); tol = 1e-6;
gamma = 1e-2;
while 1
e0 = f(b0);
J = g(b0);
step = (J'*J+gamma.*eye(size(J,2)))\(J'*e0);
b1 = b0-alpha*step;
e1 = f(b1);
S1 = sum(e1.^2);
    while S1 > S0    
        step = step/2;
        b1 = b0-alpha*step;
        e1 = f(b1);
        S1 = sum(e1.^2);
    end
    if norm(b1-b0) <tol || abs(S1-S0) < tol
        break;
    else
        b0 = b1;
        S0 = S1;
    end
end
b0
b1
sigmah2 = sum(e1.^2)/(length(x) - length(b0));
% SE = sqrt(diag(sigmah2*eye(2)*1\(J'*J)));
SE = sqrt(diag(sigmah2*inv(J'*J)));

zsc = b1./SE;
pval = 2*(1-normcdf(abs(zsc)));
SE
% tohle ne:
%     e = f(b0);
%     J = g(b0);
%     step = (J'*J)\(J'*e);
% while S > S0
%     step = step/2
%     b = b-alpha*step;
%     e = f(b);
%     S = sum(e.^2);
% end