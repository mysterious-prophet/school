function prostaiterace

	% puvodni rovnice f1, f2
	function f2=f2(x,y) % f2(x,y) = 0
		f2=x^2 + 5*y -4;
	end
						
	function f1=f1(x,y) % f1(x,y) = 0
		f1 = x^2 + 4*x - y^2 - 2*y -1;
	end

	% parametricke vyjadreni x,y
	function phi1=phi1(x,y) % x = phi1(x,y)
		phi1 = (y^2 + 2*y +1 -x^2)/4;
	end		
	
	function phi2=phi2(x,y) % y = phi2(x,y)
		phi2=(4-x^2)/5;
	end
	

n  = 20;	% pocet kroku
x0 = 0;	% pocatecni odhad x
y0 = 0;	% pocatecni odhad y

for i=1:n
	% zobrazeni aktualni velikosti x,y a hodnot f1, f2 v danych bodech
	disp( ['Krok ' num2str(i) ' (x0, y0)=(' ...
		num2str(x0) ', ' num2str(y0) ...
		')   (f1,f2)=(' num2str(f1(x0,y0)) ...
		', ' num2str(f2(x0,y0)) ')' ] );
	% iteracni krok - vypocet z parametrickych rovnic
	xn = phi1(x0,y0);
	yn = phi2(x0,y0);
	x0 = xn;
	y0 = yn;
end

end