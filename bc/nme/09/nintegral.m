function nintegral(m)
% m = pocet kroku, f = funkce (1 ... exp(x), 2 ... sin^3(x))


%a=1; b=5;
a=pi/6; b= pi/2
function f=f(x)
	f=sin(x)^3;
end

r=(b-a)/m; % velikost kroku


% obdelnikova metoa
S=0;
for i=a:r:b-r
	S=S+r*(f(i+r/2));
end
disp(['obdelnikova metoda ']);
S


% lichobeznikova metoda
S=f(a)/2 + f(b)/2;
for i=a+r:r:b-r
    S = S + f(i);
end
S = S*r;

disp(['lichobeznikova metoda ']);
S


% simpsonovo pravidlo
S=f(a)+f(b);
j=1;
for i = a+r:r:b-r
    if(mod(j,2) == 0)
        S = S + 2*f(i);
    else
        S = S + 4*f(i);
    end
    j =j + 1 ;
end
S=S*r/3;

disp(['simpsonovo pravidlo ']);
S

end
