function J = IntegrovaniVzorkovaniPoIntervalech(z_integ, z_inter)
%INTEGROVANIVZORKOVANIPOINTERVALECH Integrovani po intevalech pomoci zakladni vzorkovanci metody.
%   J = INTEGROVANIVZORKOVANIPOINTERVALECH(z_integ, z_inter) integruje dany
%   interval pomoci zakladni vzorkovaci metody aplikovanou na podintervaly.
%   V jednotlivych podintervalech je ruzny podil celkoveho poctu vzorku.
%   
%   z_integ ... struktura obsahujici zadany integral
%
%   z_integ.f ... integrovana funkce
%   z_integ.a ... dolni hranice integrovaneho intervalu
%   z_integ.b ... horni hranice integrovaneho intervalu
%   z_integ.N_max ... maximalni velikost vytvoreneho vzorku
%   z_integ.c_max ... maximum funkce na intervalu
%
%   z_inter ... struktura obsahujici specifikaci podintervalu
%
%   z_inter.intervaly ... pole obsahujici hranice podintervalu, neobsahuje
%   body hranice původniho intervalu
%   z_inter.N_intervaly ... pole obsahujici velikosti vzorku jako podil
%   celkoveho poctu.
%
%   J ... vysledna hodnota integralu
%
%   Skriptum str. 79

% ziskani intervalu, doplneni o hranicni body
intervaly = [z_integ.a, z_inter.intervaly, z_integ.b];
% velikost vzorku v intervalech
N_intervaly = ceil(z_inter.N_intervaly * z_integ.N_max);

% prubezna hodnota vysledku
J = 0;

% prochazeni jednotlivych intevalu
for int_idx = 1:numel(N_intervaly)
    % vytvoreni kopie puvodniho zadani
    % kopie bude specifikovana na soucasny interval
    zadani_now = z_integ;
    
    % pocet vzorku pro soucasny interval
    N_now = N_intervaly(int_idx);
    % hranice soucasneho intervalu
    a_now = intervaly(int_idx);
    b_now = intervaly(int_idx + 1);
    
    % uprava soucasneho zadani pro tento interval
    zadani_now.a = a_now;
    zadani_now.b = b_now;
    zadani_now.N = N_now;
    
    % vypocet integralu na soucasnem intervalu
    J_now = IntegrovaniVzorkovaniZaklad(zadani_now);
    
    % pricteni vysledku z tohoto intervalu k celkovemu vysledku integralu
    J = J + J_now;
end
end