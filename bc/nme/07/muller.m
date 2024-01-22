function muller

	function f=f(x)
		f=4*x^3 - 2*x^2 - 4*x - 3;
	end

presnost=1.0e-6;

n=1;

x1=1;
x2=2;
x3=1.1;

y1=f(x1);
y2=f(x2);
y3=f(x3);

while (abs(y3)>presnost)
	
    disp(['Krok ' num2str(n) ' koren ' num2str(x3) ' hodnota ' num2str(y3)]);
    a1=y1/((x1-x2)*(x1-x3));
    a2=y2/((x2-x1)*(x2-x3));
    a3=y3/((x3-x1)*(x3-x2));
    A=a1+a2+a3;
    C=x2*x3*a1 + x1*x3*a2 + x1*x2*a3;
    B=-(x2+x3)*a1 -(x1+x3)*a2 -(x1+x2)*a3;

    xn=(-B+sqrt(B*B-4*A*C))/(2*A);
    xn0=(-B-sqrt(B*B-4*A*C))/(2*A);

    if abs(xn0-x3)<abs(xn-x3)
    	xn=xn0;
    end

    x1=x2;
    x2=x3;
    x3=xn;
    y1=y2;
    y2=y3;
    y3=f(xn);

    n=n+1;
    
end

end

