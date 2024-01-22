function newtonraphson

stupen=2;
h=0.01;

function dfdx=dfdx(f,x,y,h)
    dfdx= 1/(2*h) * ( f(x+h,y) - f(x-h,y) );
end

function dfdy=dfdy(f,x,y,h)
    dfdy=1/(2*h) * ( f(x,y+h) - f(x,y-h) );
end

function f1=f1(x,y)
    f1=x^2 + 4*x - y^2 - 2*y - 1;
end

function f2=f2(x,y)
    f2=x^2 + 5*y - 4;
end

n=20;
x0=1;
y0=1;

a=zeros(stupen);
b=zeros(stupen,1);

for i=1:n

	disp(['Krok ' num2str(i) ' (x0,y0)=(' num2str(x0) ',' num2str(y0) ...
	')   (f1,f2)=(' num2str(f1(x0,y0)) ',' ...
	num2str(f2(x0,y0)) ')' ] );

	a(1,1)=dfdx(@f1,x0,y0,h);
	a(1,2)=dfdy(@f1,x0,y0,h);
	a(2,1)=dfdx(@f2,x0,y0,h);
	a(2,2)=dfdy(@f2,x0,y0,h);

	b(1) = -f1(x0,y0);
	b(2) = -f2(x0,y0);

	dx=a\b;

	x0=x0+dx(1);
	y0=y0+dx(2);

end

end
