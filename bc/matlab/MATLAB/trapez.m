function I = trapez(f, a, b, m)
h = (b-a)/m;
x = a:h:b;
if ischar(f)
    y = eval(f);
else
    y = f(x);
end
I = h*(y(1)/2 + sum(y(2:end-1)+ y(end)/2));