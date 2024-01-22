function nejmctverce

% nagenerujeme si data tak, aby byly linearne zavisla
x = 1:20;
y = 1:20;

% pouzijeme funkci poissrnd, ktera nageneruje data s poissonovskym rozdelenim
ySum = poissrnd(y);

% napocitame Sk a Tk
S0 = sum(x.^0);
S1 = sum(x.^1);
S2 = sum(x.^2);
S3 = sum(x.^3);
S4 = sum(x.^4);
T0 = sum(ySum.*x.^0);
T1 = sum(ySum.*x.^1);
T2 = sum(ySum.*x.^2);

% % napocitame parametry a a b
% b= ( S2*T0 - S1*T1 ) / ( S0*S2 - S1^2 );
% a= ( S0*T1 - S1*T0 ) / ( S0*S2 - S1^2 );

% numericky resime soustavu
A=[S0, S1, S2; S1, S2, S3; S2, S3, S4];
prv_str=[T0; T1; T2];
koef=A\prv_str;


% nagenerujeme si body x, ve kterych chceme provest interpolaci
xToPrint=1:0.1:20;

% spocteme si hodnotu interpolace
%yToPrint=a*xToPrint+b;
yToPrint = koef(1)+koef(2)*xToPrint+koef(3)*xToPrint.^2;
% zobrazime
plot(x,ySum,'rx',xToPrint,yToPrint);

end
