function J = IntegrovaniVzorkovaniRelevantniVyber(z_integ, z_vyber)
%INTEGROVANIVZORKOVANIRELEVANTNIVYBER Vypocet integralu vzorkovanim s relevantnim umistenim vzorku. 
%   J = INTEGROVANIVZORKOVANIRELEVANTNIVYBER(z_integ, z_vyber) vypocita
%   odhad hodnoty integralu zadanem ve strukture z_integ pomoci vzorkovani
%   dle hustoty specifikovane ve strukture z_vyber. Pro rozdeleni vzorku by
%   mela byt relevantni hodnota integrovane funkce, aby oblasti, kde nabyva
%   integrovana funkce vysokych hodnot byly navzorkovany s vyssi hustotou.
%
%   z_integ ... struktura obsahujici zadany integral
%
%   z_integ.f ... integrovana funkce
%   z_integ.a ... dolni hranice integrovaneho intervalu
%   z_integ.b ... horni hranice integrovaneho intervalu
%   z_integ.N_max ... maximalni velikost vytvoreneho vzorku
%   z_integ.c_max ... maximum funkce na intervalu
%
%   z_vyber ... struktura obsahujici relevanntni rozdeleni vzorku
%
%   z_vyber.p ... hustota pravdepodobnosti vzorku, musi byt nornovana na
%   intervalu pres ktery se integruje
%   z_vyber.Finv ... inverzni funkce k distribucni funkci zadane hustoty
%
%   Skriptum str. 81

% vzorkovani dle zadane hustoty:
% velikost pole
dims = [z_integ.N_max, 1];
% transformace pomoci inverzni distribucni funkce
r = z_vyber.Finv(rand(dims));

% vysledek jako prumer f(r)/p(r)
J = mean(z_integ.f(r) ./ z_vyber.p(r));
end