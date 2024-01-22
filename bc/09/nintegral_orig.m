function nintegral_orig(m)
% m = pocet kroku, f = funkce (1 ... exp(x), 2 ... sin^3(x))

a=1; b=5;
%a=pi/6; b= pi/2
function f=f(x)
    f=exp(x);
	%f=sin(x)^3;
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
S = 0.5*r*(f(a) + f(b));
for i = a+r:r:b-r
   S = S + r*f(i); 
end
disp(['lichobeznikova metoda ']);
S

% simpsonovo pravidlo
S=0;
for i = a:2*r:b-2*r
    S = S + r*1/3*(f(i)+4*f(i+r)+f(i+2*r));
end
% doplnte

disp(['simpsonovo pravidlo ']);
S

end
