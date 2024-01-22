%Ukazka zamitaci metody pro hustotu s nekonecnym supportem

close all
clear variables
clc

% velikost nahodnych poli
dims = [1000, 1];


%% Postup
% z exponencialniho rozdeleni nagenerujeme normalni rozdeleni zamitaci metodou

% rovnomerne navzorkujeme plochu pod krivkou exp. rozdeleni
% ze vsech bodu vybereme pouze ty, kterou jsou pod krivkou norm. rozdeleni
% x souradnice vybranych bodu je norm. rozdelena

% normalni pdf
norm_pdf = @(x) 1/sqrt(2*pi) * exp(-0.5*(x.^2));
% exponencialni pdf
exp_pdf = @(x) exp(-x);
% exponencialni icdf
exp_icdf = @(y) -log(y);
% neprve generuje jen absolutni hodnoty normalniho rozdeleni:
% "polo"normalni
% na konci z abs hodnot udelame kladne i zaporne

% obrazek
exp_x_plot = 0:0.01:10;
% pomocna funkce bez parametru pro vykresleni exp. hustoty
plot_exp = @() plot(exp_x_plot, exp_pdf(exp_x_plot), 'red',...
    'Linewidth', 2);
% pomocna funkce bez parametru pro vykresleni norm. hustoty
plot_norm = @() plot(exp_x_plot, norm_pdf(exp_x_plot), 'blue',...
    'Linewidth', 2);

figure
hold on
plot_exp()
plot_norm()
hold off
title('Porovnání "polo"normální a exponencialní hustoty pravd.')


%% Generovani z exponencialniho rozdeleni
% "vzorkovani interalu (0, +inf)"

% generovani z exponencialniho rozedeleni
exp_x = exp_icdf(rand(dims));

% obrazek
figure;
histogram(exp_x, 'Normalization', 'pdf')
hold on
plot_exp()
hold off
title('Nagenerované hodnoty z exp. rozdělení')


%% Napocteni hustoty v hodnotach

% vypocteni hustoty exp. rozdeleni v navzorkovanych bodech
exp_y = exp_pdf(exp_x);
% vypoceteni hustoty norm. rozdeleni v navzorkovanych bodech
norm_y = norm_pdf(exp_x);

%% Generovani z U(0, f(x))
% f(x) je v tomto pripade hustota exp. rozdeleni 'exp_y'
% v navzorkovanych bodech 'exp_x'

% pro kazdou hodnotu exp_y(i) generuji jednu hodnotu z U(0, exp_y(i))
% implementace: U(0, exp_y(i)) generuji jako U(0, 1)*exp_y(i)
% provedu jako nasobeni poli po slozkach
unif_y = rand(dims) .* exp_y;
% body (exp_x(i), unif_y(i)) rovnomerene vzorkuji plochu pod krivkou hustoty exp. rozdeleni

% obrazek
figure
hold on
plot(exp_x, unif_y, '. black');
plot_exp()
plot_norm()
hold off
title('Navzorkovaná plocha pod křivkou hustoty exp. rozdělení')


%% Zamitani

% zamitam porovnanim hodnot unif_y a nomr_y
je_pod = unif_y < norm_y;
% ulozeni hodnot, ktere jsou vybrany
norm_x = exp_x(je_pod);

% obrazek
figure;
hold on
plot(norm_x, unif_y(je_pod), '. green')
plot_exp()
plot_norm()
hold off
title('Zvolené hodnoty')

%% Prevedeni z "polo"normalni rozdeleni
% u kazde hodnoty z "polo"normaniho rozdeleni se hodi minci
% s prob 0.5 hodnotu vynasobine -1, s prob 0.5 vynasobime 1 (neudelame nic)
% ziskavame timto normalni rozdeleni

% provedeni hodu minci pro kazdou z vybranych hodnot
vybrane_hodnoty = rand(size(norm_x)) < 0.5;
% porovnanim '<' dostavame logicke hodnot true/false
% true elementy vynasobime -1 
norm_x(vybrane_hodnoty) = -1 * norm_x(vybrane_hodnoty);
% v norm_x je nyni vzorek z normalniho rozdeleni

% obrazek
figure;
hold on
plot(norm_x, unif_y(je_pod), '. green')
plot_exp()
plot_norm()
hold off
title('Rozšíření na záporné hodnoty')


%% Vykresleni vzorku

x_plot = -10:0.1:10;
y_plot = norm_pdf(x_plot);
figure;
histogram(norm_x, 'Normalization', 'pdf');
hold on
plot(x_plot, y_plot, 'blue', 'Linewidth', 2);
hold off
title('Rozdělení výsledného vzorku')
% nastaveni omezeni osy y
ylim([0, 1])
