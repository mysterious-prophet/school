%Ukazka zakladni metody s inverzni distribucni funkci

close all
clear variables
clc

% velikost poli
dims  = [10000, 1];


%% Generuji z U(0, 1)

r = rand(dims);


%% Exponencialni rozdeleni

% hustota pravdepodobnosti
exp_pdf = @(x, lam) lam * exp(-lam * x);
% distribucni funkce
exp_cdf = @(x, lam) 1 - exp(-lam * x);
% nahrazuji 1-y za y
% y \in(0, 1) -> 1-y \in (0, 1)
exp_icdf = @(y, lam) -log(y)/lam;
% zvolena hodnota parametru
exp_lam = 2;

% transformace
exp_x = exp_icdf(r, exp_lam);

% vykresleni histogramu s pdf
% navzorkovani osy x
exp_plot_x = 0:0.1:5;
% vypocteni hodnot pdf
exp_plot_y = exp_pdf(exp_plot_x, exp_lam);
% vykresleni
figure;
histogram(exp_x, 'Normalization', 'pdf');
hold on
% kresleni pdf
plot(exp_plot_x, exp_plot_y, 'red', 'Linewidth', 2)
hold off
title('Exponencialni rozdeleni')


%% Cauchyovo rozdeleni

cauch_pdf = @(x) 1./(pi*(1 + x.^2));
cauch_cdf = @(x) 0.5 + 1/pi * atan(x);
cauch_icdf = @(y) tan(pi*(y - 0.5));
% transformace
cauch_x = cauch_icdf(r);
% navzorkovani osy x
cauch_plot_x = -5:0.1:5;
cauch_plot_y = cauch_pdf(cauch_plot_x);
% vykresleni
figure;
% subplot: pro vlozeni vicero grafu do jedne figury
subplot(1, 3, 1);
% histogram vypada osklive: je to dusledek vlastnosti rozdeleni, ne chyba
histogram(cauch_x, 'Normalization', 'pdf');
title('Histogram')
% dalsi graf
subplot(1, 3, 2);
% histogram hodnot v intervalu (-5, 5), normalizace postrada smysl
histogram(cauch_x(abs(cauch_x) < 5));
title('Histogram hodnot na (-5, 5)')
subplot(1, 3, 3);
plot(cauch_plot_x, cauch_plot_y, 'red', 'Linewidth', 2)
title('Cauchy rozdeleni pdf')


%% Normalni rozdeleni

% pro definici funkci pouziji preddefinovane: uvazuji N(0, 1)
% pdf: normpdf
% cdf: normcdf
% icdf: norminv

% transformace
norm_x = norminv(r);
% vykresleni
norm_plot_x = -10:0.1:10;
norm_plot_y = normpdf(norm_plot_x);
figure;
histogram(norm_x, 'Normalization', 'pdf');
hold on
plot(norm_plot_x, norm_plot_y, 'red', 'Linewidth', 2);
title('Normani rozdeleni N(0, 1)')
