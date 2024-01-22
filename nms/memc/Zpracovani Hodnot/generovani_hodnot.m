%Generovani nahodnych vysledku integracnich metod
close all
clear variables
clc

%   Je vhodne oddelit kod, ktery generuje data, a ktery je zpracovava.
%   Je tim zprehlednen cely program. Navic plati, ze pokud generovani trva
%   dlouhou dobu, pak je vhodne si data ulozit, aby nebylo nutne vysledky
%   generovat pokazde, kdyz maji byt zpracovany.

%% Nastaveni
% velikost vzorku uvnitr integracnich metod
velikost_vzorku_metody = 1000000;

% velikost vzorku vysledku nahodnych metod
velikost_vysledku = 1000;

% struktura obsahujici zadani integracni ulohy
% zadani vytvoreno pomoci funkce (umistena na konci tohoto souboru)
zadani = GetZadani();

%% Definovani metod
% funkce vytvarejici nahodne odhady integralu ze zadani
metoda1 = @(N) MetodaVzorkovaniFunkce(zadani, N);
metoda2 = @(N) MetodaVzorkovaniPlochy(zadani, N);

%% Generovani nezavislych vysledku
% vytvoreni prazdnych poli
X1 = nan([velikost_vysledku, 1]);
X2 = nan([velikost_vysledku, 1]);

% v cyklu jsou opetovne volany integracni metody
% vysledky jsou ukadany do poli
for i=1:velikost_vysledku
    X1(i) = metoda1(velikost_vzorku_metody);
    X2(i) = metoda2(velikost_vzorku_metody);
    % vypis prubehu
    disp("Hotovo: " + i / velikost_vysledku * 100 + "%")
end

%% Ulozeni vysledku
nazev_souboru = 'nahodne_vzorky.mat';
% ulozeni promenych z workspace do souboru
save(nazev_souboru, 'X1', 'X2')

%% Funkce

function zadani = GetZadani()
%Vytvoreni struktury se zadanim integralu

% integrovana funkce
zadani.f = @(x) exp(x);
% interval integralu
zadani.a = 0;
zadani.b = 1;
% zname maximum funkce na intevalu
% analyticky odvozene
zadani.c_max = zadani.f(zadani.b);
end

function J = MetodaVzorkovaniFunkce(zadani, N)
%Vypocet integralu vzorkovanim funkce

% delka intervalu
delka = zadani.b - zadani.a;

% vzorkovani z U(0, 1)
r = rand([N, 1]);
% vzorkovani z U(a, b)
r = r * delka + zadani.a;

% odhad integralu
J = delka * mean(zadani.f(r));
end

function J = MetodaVzorkovaniPlochy(zadani, N)
%Vypocet integralu vzorkovanim plochy

% delka intervalu
delka = zadani.b - zadani.a;

% plocha vzorkovaneho obdelnika
S = delka * zadani.c_max;

% vzorkovani osy x, U(a, b)
r_x = rand([N, 1]) * delka + zadani.a;
% vzorkovani osy y, U(0, c_max)
r_y = rand([N, 1]) * zadani.c_max;

% vyhodnoceni, zda jsou body pod krivkou
jsou_pod = r_y < zadani.f(r_x);

% odhad integralu
J = mean(jsou_pod) * S;
end
