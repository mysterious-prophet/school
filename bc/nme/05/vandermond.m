%interpolace polynomem

%zadana (zmerena) x a y
x=[0.1 1 1.1 1.2 1.3 2    3    4    5   ];
y=[1   1 0.9 0.2 0.1 0.01 0.01 0.01 0.01];

%v techto bodech chceme spocitat interpolaci
xToPrint=0.1:0.01:5;

%sestrojime vandermondovu matici
matice=vander(x);

%resime soustavu matice * koeficienty = y
koeficienty=matice\y';

%spoctememe si hodnoty v xToPrint
yToPrint=polyval(koeficienty,xToPrint);

%zobrazime originalni data jako cervene krizky a navic interpolaci jako caru
plot(x,y,'rx',xToPrint,yToPrint,'g-');
title('Polynom stupne 8');
