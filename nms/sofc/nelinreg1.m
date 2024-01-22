data = load('data.txt');
yy = data(:, 1);
xx = data(:, 2);

JJ = @(beta)[(1 - exp(beta(2)*xx)) -beta(1)*xx.*(1 - exp(beta(2)*xx))];
r = @(beta) yy - beta(1)*(1 - exp(-beta(2) * xx));

b0 = [250 5e-4]';
delta = 1e-10;
lambda = 1e-3;
while 1 
   e = r(b0);
   J = JJ(b0);
   krok = (J'*J + lambda*eye(length(b0)))\(J'*e);
   b1 = b0 - krok;
   sse0 = e'*e;
   e1 = r(b1);
   sse1 = e1'*e1;
   while sse1 > sse0
      krok = krok/2;
      b1 = b0 - krok;
      e1 = r(b1);
      sse1 = e1'*e1;
   end
   if (norm(b1 - b0) > delta)
       b0 = b1;
       sse0 = sse1;
   else
       break
   end
end

plot(xx, yy, 'ok');
hold on
y = @(beta) beta(1)*(1 - exp(-beta(2) * xx));
y1 = y(b1);
plot(xx, y1, '-b');
hold off