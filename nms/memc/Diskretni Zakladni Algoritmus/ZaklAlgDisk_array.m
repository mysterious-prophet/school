function k = ZaklAlgDisk_array(p)
%ZAKLALGDISK_ARRAY Zakladni algoritmus pro generovani z diskretni nahodne veliciny rozdelene dle pravdepodobnosti v poli.
%   k = ZAKLALGDISK_ARRAY(p) vytvori nahodnou hodnotu k rozdelenou dle
%   pravdepodobnosti ve vektoru p
%
%   p ... pole pravdepodobnosti, soucet hodnot musi byt roven jedne
%   k ... jedna realizace nahodne veliciny rozdelene dle p, index z p
%
% Prevzato z:
% Virius, M.: Metoda Monte Carlo. Praha, Vydavatelství ČVUT 2010. ISBN 978-80-01-04595-4
% Strana 24

% kontrola normalizace pole p
KontrolaNormalizace(p)


%% Algoritmus

% nageneruji jednu hodnotu z U(0,1)
S = rand();
% inicializace indexu, MATLAB indexuje od 1
k = 1;
% zapocteme prvni hodnotu
S = S - p(k);

while S > 0
    k = k + 1;
    S = S - p(k);
end
% na konci algoritmu je v promene k ulozen index
end

function KontrolaNormalizace(p)
%Kontrola jestli je soucet pole p rovny 1

% sectu hodnoty v poli
p_sum = sum(p, 'all');
% zkontroluji jestli je rovno jedne, az na numerickou chybu
if abs(p_sum - 1) < 0.00001
    % je rovno jedne, nic nedelam
else
    % neni rovno jedne
    % zavolam error
    error('Soucet pravdepodobnosti v poli p neni roven jedne.')
end
end