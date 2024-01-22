function J = IntegrovaniVzorkovaniHlavniCast(z_integ, z_hlc)
%INTEGROVANIVZORKOVANIHLAVNICAST Vypocet integralu na konecnem intervalu vzorkovanim s vyjmutou hlavni casti.
%   J = INTEGROVANIVZORKOVANIHLAVNICAST(z_integ, z_hlc) vypocte integral
%   zadane funkce ze struktury z_integ pomoci vzorkovani s odebranou hlavni
%   casti, ktera je specifikovala ve strukture z_hlc.
%
%   z_integ ... struktura obsahujici zadany integral
%
%   z_integ.f ... integrovana funkce
%   z_integ.a ... dolni hranice integrovaneho intervalu
%   z_integ.b ... horni hranice integrovaneho intervalu
%   z_integ.N_max ... maximalni velikost vytvoreneho vzorku
%   z_integ.c_max ... maximum funkce na intervalu
%
%   z_hlc ... struktura obsahujici zadanou hlavni cast
%
%   z_hlc.g ... funkce hranice hlavni casti
%   z_hlc.c_min ... hodnota minima funkce hranice hlavni casti
%   z_hlc.S ... plocha hlavni casti
%
%   J ... vysledna hodnota integralu
%
%   Skriptum str. 78 

%% Prevedeni ulohy na obycejne vzorkovani
% kopie vlozeneho zadani
zadani_now = z_integ;
% upraveni integrovane funkce
% od integrovane funkce je odectena funkce hranice hlavni casti 
zadani_now.f = @(x) z_integ.f(x) - z_hlc.g(x);
zadani_now.c_max = z_integ.c_max - z_hlc.c_min;

% zavolani zakladni integrovaci funce
% vysledek je mira plochy bez hlavni casti
J = IntegrovaniVzorkovaniZaklad(zadani_now);

% pridani plochy hlavni casti
J = J + z_hlc.S;
end
