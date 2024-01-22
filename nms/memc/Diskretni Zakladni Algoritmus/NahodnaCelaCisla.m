function r = NahodnaCelaCisla(N, dims)
%NAHODNACELACISLA Generovani nahodnych celych cisel 1 az N.
%   r = NAHODNACELACISLA(N, dims) nageneruje rovnomerne rozdelena cela
%   cisla 1 az N do pole r o rozmerech dims
%
%   N ... maximalni generovane cislo
%   dims ... rozmery vysledneho pole
%   r ... pole obsahujici vysledna nahodna cisla 1 az N
%
% Prevzato z:
% Virius, M.: Metoda Monte Carlo. Praha, Vydavatelství ČVUT 2010. ISBN 978-80-01-04595-4
% Strana 25

% vygeneruji vsechny hodnoty U(0, 1)
r = rand(dims);
% pouziji algoritmus ze skripta, floor vraci dolni celou cast
% operace jsou provadeny po prvcich pole r
r = floor(N * r) + 1;
end