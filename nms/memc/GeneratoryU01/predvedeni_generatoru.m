%Predstaveni vlastnosti generatoru z U(0, 1)
 
close all
clear variables
clc

% velikost nagenerovaneho pole
dims = [1000000, 1];



%% Generovani hodnot

%dostupne generatory
generators = ["square", "gen50", "randu"];
% pocet generatoru
gen_num = numel(generators);

R = nan([dims, gen_num]);
R(:, :, 1) = rand(dims);
% generovani pomoci vytvorene funkce
R(:, :, 2) = GenGenerator(dims, generators(1));
R(:, :, 3) = GenGenerator(dims, generators(2));
R(:, :, 4) = GenGenerator(dims, generators(3));

% dokumentace funkce:
% doc GenGenerator


%% Histogramy

figure;
for i = 1:gen_num
    subplot(1, gen_num, i)
    histogram(R(:, :, i))
    title(generators(i))
end


%% Zobrazeni Middle-square metody

% vykresleni nagenerovane posloupnosti
figure
subplot(1, 2, 1)
plot(R(:, :, 2), '. black')
% nastaveni logaritmickeho meritka x osy
set(gca, 'XScale', 'log')
% popisky
title('Middle-square metoda: nagenerovana řada')
xlabel('pořadí členů')
ylabel('hodnoty')

% histogram nenulovych hodnot
subplot(1, 2, 2)
SQ_nonzero = R(:, :, 2);
SQ_nonzero(SQ_nonzero == 0) = [];
histogram(SQ_nonzero)
title('Histogram nenulových hodnot')


%% Statistiky

% prumery
% mean: prumer pres zadane dimenze
% squeete: prerovnani dimenzi pole, z dimenze [1, 3, 1] udela [3, 1]
all_means = squeeze(mean(R, [1, 2]));
% rozptyly
all_vars = squeeze(var(R, [], [1, 2]));


%% Prevedeni na normalne rozdelene veliciny
% pouziti inverzni cdf
N = norminv(R);

%% Histogramy
x_plot = -5:0.1:5;
y_plot = normpdf(x_plot);
figure;
for i=1:gen_num
    subplot(1, gen_num, i)
    histogram(N(:, :, i), 'Normalization', 'pdf')
    hold on
    plot(x_plot, y_plot, 'red', 'Linewidth', 2);
    hold off
    title(generators(i))
end
