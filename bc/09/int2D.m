function int2D

% integrovana funkce 
%f = inline('abs(sin(pi.^2.*((x-0.5).^2+(y-0.5).^2)))','x','y');
f = inline('x+y','x','y'); % od 1 do 1 vyjde 1

h=0.5e-2;

a=1;
b=1;

xArr=0:h:a-h;   % interval x
yArr=0:h:b-h;   % interval y

integral=0;

tic
for xi=xArr % pruchod pres x
    for yi=yArr % pruchod pres y
    % obdelnikove pravidlo v pulce podintervalu
	    integral=integral+f(xi+h/2,yi+h/2);
    end
    
end
integral = integral*h^2;
toc

integral



inty = [];    % pole spocitanych integralu dy
integral = 0;
i = 0;        % budeme potrebovat index do pole
xArr=0:h:a;   % interval x - budeme potrebovat i pravy krajni bod
yArr=0:h:b-h; % interval y

tic
for xi=xArr
    i = i+1;
    inty(i) = 0;
    for yi=yArr
       % ulozime pro kazde x integral v dy, integrujeme lichobeznikovym pravidlem
	    inty(i)=inty(i) + 0.5*( f(xi,yi) + f(xi,yi+h) );
    end
end

for i=1:size(inty,2)-1
    % opet lichobezniko pravidlo. 
    % pouzivame index i+1, proto jsme porebovali pravy krajni bod v x
    integral = integral + 0.5*(inty(i)+inty(i+1));
end


integral = integral*h^2;
toc

integral


end
