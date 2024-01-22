%Ukazka zamitaci metody pro hustotu s konecnym supportem

close all
clear variables
clc

% velikost poli
dims  = [10000, 1];


%% Definuji vlastni rozdeleni

% x\in(0, pi)
x_lim = [0, pi];
% pdf
my_pdf = @(x) 0.5 * sin(x);

% y souradnice hranice vzorkovane oblasti
% hodnoty urceny z travu pdf: minimum 0, maximum je 0.5
y_lim = [0, 0.5];

% vykresleni pdf
x_plot = x_lim(1):0.01:x_lim(2);
y_plot = my_pdf(x_plot);
figure;
plot(x_plot, y_plot, 'magenta', 'Linewidth', 2)
title('Zadana hustota pravdepodobnosti')
xlabel('x')
ylabel('f(x)')


%% Generovani bodu uvnitr oblasti
% nahodna souradnice v kazdem smeru
% bod (x, y) kde x\in(0, pi), y\in(0, maxY)

% vytvoreni nahodne x souradnice v intervalu [0, pi]
% delka intervalu
x_len = x_lim(2) - x_lim(1);
% generovani a transformace
x_coord = rand(dims) * x_len + x_lim(1);

% obdobne pro y souradnici
y_len = y_lim(2) - y_lim(1);
y_coord = rand(dims) * y_len + y_lim(1);

% vykresleni bodu do obrazku
figure;
hold on
plot(x_coord, y_coord, '. black')
plot(x_plot, y_plot, 'magenta', 'Linewidth', 2)
hold off
title('Nahodne body v oblasti')
xlabel('x')
ylabel('f(x)')


%% Zamitnuti bodu pod pdf

% ponechame body, ktere jsou pod krivkou pdf

% vyhodnoceni pdf v nahodnych x souradnicich
y_pdf = my_pdf(x_coord);
% u kazdeho vysledku porovname po slozkach s nahodnou y souradnici
je_pod = y_coord < y_pdf;
% udelame vyber pouze bodu pod pdf
x_vyber = x_coord(je_pod);
y_vyber = y_coord(je_pod);

% vykresleni
figure;
hold on
plot(x_vyber, y_vyber, '. green')
plot(x_plot, y_plot, 'magenta', 'Linewidth', 2)
hold off
title('Zvolene body v oblasti')
xlabel('x')
ylabel('f(x)')


%% Ziskane rozdeleni
% x souradnice ma nyni rozdeleni dle zadane pdf

% vykresleni
figure;
histogram(x_vyber, 'Normalization', 'pdf')
hold on
plot(x_plot, y_plot, 'magenta', 'Linewidth', 2)
hold off
title('Ziskane rozdeleni vs. hustota pravdepodobnosti')
xlabel('x')
ylabel('f(x)')

% vypis poctu ziskanych hodnoty
disp('Nagenerovano hodnot:')
% numel: number of elements
disp(numel(x_vyber))
