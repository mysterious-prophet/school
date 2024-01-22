function r = HodMinci(dims)
%HODMINCI Nahodne hody minci.
%   r = HODMINCI(dims) nageneruje nahodne hody minci do pole r o rozmerech dims
%
%   dims ... rozmery vysledneho pole
%   r ... vysledne pole obsahujici nahodne hody minci, hodnoty 1 nebo 2
%
% Prevzato z:
% Virius, M.: Metoda Monte Carlo. Praha, Vydavatelství ČVUT 2010. ISBN 978-80-01-04595-4
% Strana 24

% nahodne hodnoty z U(0,1)
r = rand(dims);
% rozhodnuti jestli padla panna nebo orel
r = r > 0.5;
% v poli r jsou logicke hodnoty 0 a 1
% prevedu na cisla 1 a 2
r = r + 1;
end