%Predvedeni metod pro generovani ze standardniho normalniho rozdeleni

close all
clear variables
clc


%% Predvedeni vlastnosti souctu velicin z U(0, 1)
% ukazka zmen tvaru histogramu pro
% soucty nezavislych nahodnych velicin z U(0, 1)

% pocet scitanych hodnot
N = 12;
% velikost negenerovaneho vzorku
dim = 100000;

% generovani hodnoty pomoci souctu N hodnot rozdelenych z U(0, 1)
% vygeneruje se pole a secte se ve druhe dimenzi
% druhy argument ve funkci sum urcuje soucet v radcich
R = sum(rand(dim, N), 2);


%% Studium vlastnosti souctu

% histogram
figure;
histogram(R)
title('Toto nejsou normálně rozdělená data')

% stredni hodnota
mean_R = mean(R);
% rozptyl
var_R = var(R);
% vypist hodnot do konzole
disp("Střední hodnota R: " + mean_R)
disp("Rozptyl R: " +  var_R)


%% Pozorovani
% U(0, 1) ma stredni hodnotu 0.5,
%   pak ma soucet N hodnot stredni hodnotu N * 0.5
%   toto odpovida pozorovani
% pokud od souctu odecteme N *0.5, pak bude mit vysledek stredni hodnotu 0

% U(0, 1) ma rozptyl 1/12,
%   pak ma soucet N hodnot rozptyl N * 1/12
%   toto odpovida pozorovani
% pokud soucet vydelime sqrt(N/12), pak bude mit vysledek rozptyl 1


%% Transformace souctu
% upravime postup generujici soucty
% aby mela vysledna velicina stredni hodnotu 0 a rozptyl 1

% generovani z transformovaneho souctu
Rtrans = (sum(rand(dim, N), 2) - 0.5*N) * sqrt(12/N);
% zobrazeni transformovaneho vzorku
figure;
histogram(Rtrans, 'Normalization', 'pdf')
% prikresleni  hustoty N(0, 1)
x_plot = -5:0.01:5;
y_plot = normpdf(x_plot);
hold on
plot(x_plot, y_plot, 'red', 'Linewidth', 2)
hold off
title('Toto také nejsou normálně rozdělená data')

% stredni hodnota
mean_Rt = mean(Rtrans);
% rozptyl
var_Rt = var(Rtrans);

% vypis hodnot do konzole
disp("Střední hodnota Rtrans: " + mean_Rt)
disp("Rozptyl Rtrans: " +  var_Rt)

% je mozne menit hodnoty N a sledovat zmeny tvaru histogramu pro N=1, N=2,...

%% Alternativni metoda
% alternativni metoda, ktera je nezavisla na souctech U(0, 1)
% dle skripta, str. 48

% generovani paru hodnot z U(0, 1), ze kterych jsou vytvoreny pary z N(0, 1)
% definice poctu paru
sample_half_size = ceil(dim/2);
% nagenerovani pole z U(0, 1), ktere na rozmery sample_half_size x 2
r = rand(sample_half_size, 2);
% aplikace transfomace na prvni cleny paru
% r(:, 1) vybira prvni soupec
r(:, 1) = sqrt(-2*log(r(:, 1)));
% aplikace transfomace na druhe cleny paru
r(:, 2) = 2*pi*r(:, 2);
% další transformace
% vytvoreni pole, ktere na rozmery 2*sample_half_size x 1
% [poleA; poleB] slouci pole pod sebe: [[1;2;3];[4;5;6]] = [1;2;3;4;5;6]
% provedeni finalni transfomace dle skripta
Ralt = [...
    r(:, 1) .* cos(r(:, 2));...
    r(:, 1) .* sin(r(:, 2))];

% vykresleni histogramu
figure;
histogram(Ralt, 'Normalization', 'pdf')
hold on
% vykresleni normal pdf
plot(x_plot, y_plot, 'red', 'Linewidth', 2)
hold off
title('Alternativni metoda')


%% Statisticke testovani

% k dispozici jsou pole Rtrans a Ralt
% testujeme normalitu obou vzorku
% lillieforsuv test normality
[h_trans, p_trans] = lillietest(Rtrans);
[h_alt, p_alt] = lillietest(Ralt);
% vypis vysledku
disp("***Testy normality***")
disp("Vysledek pro soucet U(0, 1):")
disp("h = " + h_trans + ", p = " + p_trans)
disp("Vysledek pro alternativni postup:")
disp("h = " + h_alt + ", p = " + p_alt)

% je mozne pozorovat ruzne vysledky testu pro ruzne velke vzorky
% nazorne pri zmene hodnoty promene dim
