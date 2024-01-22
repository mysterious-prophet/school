function [r_x, r_y] = VzorkovaniRovn(dims, x_min, x_max, y_min, y_max)
%VZORKOVANIROVN Rovnomerne rozdelene body na obdelniku.
%   [r_x, r_y] = VZORKOVANIROVN(dims, x_min, x_max, y_min, y_max) generuje
%   souradnice r_x a r_y rovnomerne nahodne umistenych bodu na obdelniku
%   ohranicenem body (x_min, y_min) a (x_max, y_max). Vysledna pole
%   souradnice r_x a r_y maji dimenzi dims
%
%   dims ... dimenze vyslednych poli
%   x_min ... minimalni x souradnice obdelniku
%   x_max ... maximalni x souradnice obdelniku
%   y_min ... minimalni y souradnice obdelniku
%   y_max ... maximalni y souradnice obdelniku
%
%   r_x ... x souradnice vyslednych bodu v poli o rozmerech dims
%   r_y ... y souradnice vyslednych bodu v poli o rozmerech dims


% rovnomerne vzorkovani osy x
r_x = rand(dims);
% transformace na interval
r_x = r_x * (x_max - x_min) + x_min;

% rovnomerne vzorkovani osy y
r_y = rand(dims);
r_y = r_y * (y_max - y_min) + y_min;

end