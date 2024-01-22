function nintegral(m)
% m = pocet kroku, f = funkce (1 ... exp(x), 2 ... sin^3(x))

a=1; b=5;
%a=pi/6; b= pi/2
function f=f(x)
	f=sin(x);
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
S=0;

% doplnte

disp(['lichobeznikova metoda ']);
S

% simpsonovo pravidlo
S=0;

% doplnte

disp(['simpsonovo pravidlo ']);
S

end
