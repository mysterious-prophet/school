function J = IntegrovaniVzorkovaniFunkce(zadani)
%INTEGROVANIVZORKOVANIFUNKCE Vypocet integralu pomoci vzorkovani funkce.
%   J = INTEGROVANIVZORKOVANIFUNKCE(zadani) vypocte hodnotu integralu J,
%   ktery je zadany ve strukture zadani pomoci metody vzorkovani funkce.
%
%   zadani ... struktura obsahujici zadany integral
%
%   zadani.f ... integrovana funkce
%   zadani.a ... dolni hranice integrovaneho intervalu
%   zadani.b ... horni hranice integrovaneho intervalu
%   zadani.N_max ... maximalni velikost vytvoreneho vzorku
%
%   J ... vysledna hodnota integralu
%
%   Skriptum str. 77

%% Generovani rovnomerne rozdelenych hodnot na intervalu (a, b)
% velikost nagenerovaneho pole
dims = [zadani.N_max, 1];
% generovani z U(0, 1);
r = rand(dims);
% transformace na U(a, b)
r = r * (zadani.b - zadani.a) + zadani.a;

% vysledek je (b - a) krat prumer hodnot f(r)
J = (zadani.b - zadani.a) * mean(zadani.f(r));
end