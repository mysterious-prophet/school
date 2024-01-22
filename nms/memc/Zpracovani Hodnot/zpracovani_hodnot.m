%Zpracovani vygenerovanych nahodnych vzorku
close all
clear variables
clc

%% Nacteni hodnot ze souboru
nazev_souboru = 'nahodne_vzorky.mat';
% do workspace nactu hodnoty ze souboru
load(nazev_souboru, 'X1', 'X2')
% popisky dat
popisky = ["vz. funkce", "vz. plochy"];
% znamy teoreticky vysledek vychozi ulohy
J = exp(1) - 1;

%% Graficka analyza
% histogramy
figure
hold on
histogram(X1);
histogram(X2);
hold off
title("Rozdělení vzorků hodnot")
% pridani legendy
legend(popisky)
% pozorujeme, ze metoda vz. plochy ma vetsi rozptyl
% pozorujeme, ze obe metody maji blizke hodnoty modu
% (modus je poloha maxima hustoty)

% boxplots
figure
boxplot([X1, X2], 'labels', popisky)
title("Krabicové grafy")
% pozorujeme, ze metoda vz. funkce ma mensi mezikvartilove rozpeti
% pozorujeme, ze hodnoty medianu si jsou blizke

% zobrazeni dat v zavislosti na poradi
figure
hold on
plot(X1, '. red')
plot(X2, '. blue')
hold off
title("Data jako řady")
legend(popisky)
% nepozorujeme zadnou zavislost

%% Statistiky
% stredni hodnoty
m1 = mean(X1);
m2 = mean(X2);
% rozptyly
v1 = var(X1);
v2 = var(X2);

%% Odhad chyby Ceb. nerovnosti
% skriptum str. 18

% Cebysevova nerovnost:
% Pr(|prumer - str.hodnota| >= a) <= var / (a^2)
% s pravdepodobnosti vetsi rovnou 1 - a plati
% |prumer - str.hodnota| <= sqrt(var / (N*a))
% |prumer - str.hodnota|  je odhadovana chyba

% definuji hodnotu odhadu chyby jako funkci
% rozptylu, pravdepodobnosti a poctu pozorovani
ceb_odhad = @(v, a, N) sqrt(v./(N * (1 - a)));

% pravdepodobnost pro kterou je proveden odhad
a = 0.99;
% velikost vzorku, stejna pro oba vzorky
N = numel(X1);

% hranice pro jednotlive vzorky
h1 = ceb_odhad(v1, a, N);
h2 = ceb_odhad(v2, a, N);
% vypis hodnot
disp("Pravdepodobnost odhadu: " + a)
disp("Odhadovana chyba prvniho vzorku: " + h1)
disp("Odhadovana chyba druheho vzorku: " + h2)
% pozorujeme, ze odhadovana chyba metody vz. plochy je vetsi

% s pravdepodobnosti vetsi rovnou 'a' odhadujeme, ze spravny vysledek lezi v intervalu:
% prumer vzorku +- hranice

%% Testy pomoci norm. rozdeleni
% pokud by vzorky byly normalne rozdelene, pak
% je mozne pouzivat testy vychazejici z normalniho rozdeleni

% testujeme normalitu
% H0: vzorek je normalne rozdeleny, H1: neni norm. rozdeleny
% default hladina 0.95
hyp_norm1 = lillietest(X1);
hyp_norm2 = lillietest(X2);

disp("Zamitnuti normality prvniho vzorku: " + hyp_norm1)
disp("Zamitnuti normality druheho vzorku: " + hyp_norm2)

% pri zamitnuti normality nemaji nasledujici testy statistickou relevanci

% test, zda-li jsou stredni hodnoty vzorku rovny teor. vysledku
% default hladina 0.95
hyp_teor_vysl1 = ttest(X1, J);
hyp_teor_vysl2 = ttest(X2, J);

disp("Zamitnuti spravnosti prumeru prvniho vzorku: " + hyp_teor_vysl1)
disp("Zamitnuti spravnosti prumeru druheho vzorku: " + hyp_teor_vysl2)

% test, zda-li si jsou rozptyly vzorku rovny
% H0: rozptyly jsou rovny, H1: nejsou si rovny
% default hladina 0.95
hyp_var_rovny = vartest2(X1, X2);
disp("Zamitnuti rovnosti rozptylu obou vzorku (oproti =/=): " + hyp_var_rovny)
% zamitame rovnost rozptylu ve prospech nerovnosti rozptylu

% test, zda-li si jsou rozptyly vzorku rovny
% H0: rozptyly rovny, H1: druhy vzorek ma mensi rozptyl
hyp_var_rovny2 = vartest2(X1, X2, 'Tail', 'right');
disp("Zamitnuti rovnosti rozptylu obou vzorku (oproti >): " + hyp_var_rovny2)
% nezamitame rovnost rozptylu oproti moznosti, ze
% rozptyl druheho vzorku je mensi nez rozptyl prvniho
