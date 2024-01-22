function r = HodKostkou(dims)
%HODKOSTKOU Generovani nahodnych hodnot 1 az 6;
%   r = HODKOSTKOU(dims) nageneruje nahodne hody kostkou do pole r o
%   rozmerech dims
%
%   dims ... velikost vysledneho pole
%   r ... pole obsahuje nahodne hodnoty 1 az 6

% jedna se o specialni pripad generovani nahodnych hodnot 1 az N, kde N = 6
r = NahodnaCelaCisla(6, dims);
end