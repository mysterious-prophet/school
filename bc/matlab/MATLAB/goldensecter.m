function [fm, xm] = goldensecter(f, a, b, tol)
%x = a:0.01:b;
%fx = f(x);
%plot(x, fx)

tau = (sqrt(5)-1)/2;
x1 = a + (1-tau)*(b-a); f1 = f(x1);
x2 = a+tau*(b-a); f2 = f(x2);
q = 0;

while b-a>tol
   if f1 < f2
       b = x2;
       x2 = x1;
       f2 = f1;
       x1 = a + (1 - tau)*(b - a); f1 = f(x1);
   else
       a = x1;
       x1 = x2;
       f1 = f2;
       x2 = a + tau*(b - a); f2 = f(x2);
   end
   q = q+1;
end
xm = (a+b)/2;
fm = f(xm);    
end