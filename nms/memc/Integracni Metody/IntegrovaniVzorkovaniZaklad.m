function J = IntegrovaniVzorkovaniZaklad(zadani)
%INTEGROVANIVZORKOVANIZAKLAD Vypocet integralu na konecnem intervalu zakladnim vzorkovanim.
%   J = IntegrovaniVzorkovaniZaklad(zadani) vypocita hodnotu integralu
%   zadanem ve strukture zadani. Vypocet proveden pomoci vzorkovani
%   obdelnika, ktery plne obsahuje integrovanou oblast. Je uvazovana pouze
%   nezaporna funkce na danem intervalu.
%
%   zadani ... struktura obsahujici zadany integral
%
%   zadani.f ... integrovana funkce
%   zadani.a ... dolni hranice integrovaneho intervalu
%   zadani.b ... horni hranice integrovaneho intervalu
%   zadani.N_max ... maximalni velikost vytvoreneho vzorku
%   zadani.c_max ... maximum funkce na intervalu
%
%   J ... vysledna hodnota integralu
%
%   Skriptum str. 74

% plocha obdelnika, ktery ohranicuje integrovanou plochu
S_obd = (zadani.b - zadani.a) * zadani.c_max;

% rovnomerne vzorkovani zadaneho obdelniku
dims = [zadani.N_max, 1];
x_min = zadani.a;
x_max = zadani.b;
y_min = 0;
y_max = zadani.c_max;
[r_x, r_y] = VzorkovaniRovn(dims, x_min, x_max, y_min, y_max);

% vypocet funkcni hodnoty v navzorkovanych x souradnicich
f_y =  zadani.f(r_x);
% zjisteni, zda-li je bod pod krinkou integrovane funkce
je_pod = r_y < f_y;
% pocet bodu pod krivkou
N_pod = sum(je_pod);

% podil bodu pod krivkou vuci vsem bodum
podil = N_pod/zadani.N_max;
% odhad integralu
J = podil * S_obd;
end