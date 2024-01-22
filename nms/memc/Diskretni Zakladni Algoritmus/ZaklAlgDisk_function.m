function k = ZaklAlgDisk_function(f)
%ZAKLALGDISK_FUNCTION Zakladni algoritmus pro generovani z diskretni nahodne veliciny rozdelene dle pravdepodobnostni funkce.
%   k = ZAKLALGDISK_ARRAY(p) vytvori nahodnou hodnotu k rozdelenou dle
%   pravdepodobnosti funkce f
%
%   f ... anonymni funkce definujici pravdepodobnosti
%   k ... jedna realizace nahodne veliciny rozdelene dle f
%
% Prevzato z:
% Virius, M.: Metoda Monte Carlo. Praha, Vydavatelství ČVUT 2010. ISBN 978-80-01-04595-4
% Strana 24


%% Algoritmus

% nageneruji jednu hodnotu z U(0,1)
S = rand();
% inicializace nahodne hodnoty
k = 0;
% zapocteme prvni hodnotu
S = S - f(k);

while S > 0
    k = k + 1;
    S = S - f(k);
end
% na konci algoritmu je v k ulozena nahodna hodnota dle f
end