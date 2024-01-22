%https://www.itl.nist.gov/div898/strd/nls/data/LINKS/DATA/Misra1a.dat
y = @(b) b(1)*(1-exp(-b(2)*x));
%D = csvread('data.csv');
D = load('data.txt');
yy = D(:,1);
xx = D(:,2);

JJ =@(b)[(1 - exp(b(2)*xx)) - b(1)*xx.*(1 - exp(b(2)*xx))]; 
r = @(b) yy - b(1)*(1-exp(-b(2)*xx));
%start data set
%	5.0000000000E+02		2.5000000000E+02		2.3894212918E+02
%	1.0000000000E-04		5.0000000000E-04		5.5015643181E-04

b0 = [250 5e-4]';
delta = 1e-7;
lambda = 1e-3;

while 1
    e = r(b0);
    J = JJ(b0);
    krok = (J'*J + lambda*eye(length(b0)))\(J'*e);
    b1 = b0 - krok;
    sse0 = e'*e;
    e1 = r(b1);
    sse1 = e1'*e1;
%     while sse1 > sse0
%         krok = krok/2;
%         b1 = b0 - krok;
%         e1 = r(b1);
%         sse1 = e1'*e1;
%    end
    if norm(b1 - b0) > delta
        b0 = b1;
       % sse0 = sse1;
    else
        return
    end
end

plot(xx,yy,'ok')
hold on
y = @(b) b(1)*(1-exp(-b(2)*xx));
y1 = y(b1);
plot(xx,y1,'--')
hold off