%Porovnani ruznych vzorkovacich integracnich metod

close all
clear variables
clc

% vypocet nezavislych vysledku kazdou metodou, pri statistickem testovani
N = 1000;


%% Vytvoreni struktury se zadanym integralem

% integrovana funkce
zadani_integral.f = @(x) exp(x);
% interval pres ktery se integruje
zadani_integral.a = 0;
zadani_integral.b = 1;
% maximalni hodnota: horni omezeni obdelniku
zadani_integral.c_max = exp(1);
% maximalni velikost vzorku
zadani_integral.N_max = 100000;

% vysledek pro kontrolu
I = exp(1) - exp(0);


%% Zadani pro metodu s hlavni casti

% funkce ohranicujici hlavni cast: pouzity je tayloruv rozvoj funkce
zadani_hlavni_cast.g = @(x) 1 + x + 0.5 * x.^2;
% minimalni hodnota hranicni funkce
zadani_hlavni_cast.c_min = 1;
% plocha hlavni casti
zadani_hlavni_cast.S = 1 + 0.5 + 1/6;


%% Zadani pro integrovani po intervalech

% hranicni bod intervalu, na krajich navic bude ohraniceno body 'a' a 'b'
zadani_intervaly.intervaly = [0.25, 0.5, 0.8];
% velikosti vzorku v intervalech, zadano jako podil celkove velikosti 
zadani_intervaly.N_intervaly = [0.1, 0.1, 0.4, 0.4];


%% Zadani pro uziti relevantniho vyberu

% hustota pravdepodovnosti urcujici relevanci vzorkovani
% pouzit tayloruv rozvoj integrovane funkce, normalizovano
zadani_relevantni_vyber.p = @(x) (1 + x) / (1 + 0.5);
% inverzni distribucni funkce dane hustoty, urcena pro generovani
zadani_relevantni_vyber.Finv = @(x) sqrt(1 + 3*x) - 1;


%% Zobrazeni zadani a metod

figure
% vykresleni 
ZobrazeniZadani(zadani_integral);
ZobrazeniHlavniCasti(zadani_integral, zadani_hlavni_cast);
ZobrazeniIntervalu(zadani_integral, zadani_intervaly);
ZobrazeniRelevantniVyber(zadani_integral, zadani_relevantni_vyber);
title("Integrovaná funkce s vyznačenými aspekty integračních metod")
drawnow


%% Vypocty
% vypocet pomoci ruznych metod
J_vzorkovani_zaklad = IntegrovaniVzorkovaniZaklad(zadani_integral);
J_vzorkovani_funkce = IntegrovaniVzorkovaniFunkce(zadani_integral);
J_vzorkovani_hlavni_cast = IntegrovaniVzorkovaniHlavniCast(zadani_integral, zadani_hlavni_cast);
J_vzorkovani_po_castech = IntegrovaniVzorkovaniPoIntervalech(zadani_integral, zadani_intervaly);
J_vzorkovani_relevantni = IntegrovaniVzorkovaniRelevantniVyber(zadani_integral, zadani_relevantni_vyber);


%% Vypis vysledku

disp("Integral : " + I)
disp("Odhad Vzorkování základ: " + J_vzorkovani_zaklad)
disp("Odhad Vzorkování funkce: " + J_vzorkovani_funkce)
disp("Odhad Vzorkování hl. část: " + J_vzorkovani_hlavni_cast)
disp("Odhad Vzorkování po částech: " + J_vzorkovani_po_castech)
disp("Odhad Vzorkování relevantní: " + J_vzorkovani_relevantni)


%% Ziskani nezavislych vysledku opakovanym volanim
% u kazde metody je vypocitano mnoho ruznych vysledku
% misto jednoto vysledku integrlu je ziskano nekolik
% vysledky jsou nahodne veliciny, je mozne je statiticky testovat

% vytvorime pole bunek, v kazde bunce jedna funkce obdahujici metodu
% zakladni metoda
f_all{1} = @()...
    IntegrovaniVzorkovaniZaklad(zadani_integral);
% metoda vzorkovani funkce
f_all{end + 1} = @()...
    IntegrovaniVzorkovaniFunkce(zadani_integral);
% hlavni cast metoda
f_all{end + 1} = @()...
    IntegrovaniVzorkovaniHlavniCast(zadani_integral, zadani_hlavni_cast);
% po castech medota
f_all{end + 1} = @()...
    IntegrovaniVzorkovaniPoIntervalech(zadani_integral, zadani_intervaly);
% relevantni vzorkovani metoda
f_all{end + 1} = @()...
    IntegrovaniVzorkovaniRelevantniVyber(zadani_integral, zadani_relevantni_vyber);

% vytvoreni pole pro vysledne vzorky
% kazdy sloupec odpovida vysledkum jedne metody
vzorky_all = nan(N, numel(f_all));
% vytvoreni ruznych vysledku pomoci vsech metod
disp("Generovani " + N + " vysledku integralu pro kazdou metodu...")
for metoda_idx = 1:numel(f_all)
    for beh_idx = 1:N
        vzorky_all(beh_idx, metoda_idx) = f_all{metoda_idx}();
    end
end

%% Box plot

% jmena metod pro popisky
jmena_metod = ["vz. plochy", "vz. funkce", " hl. část", "po částech", "relevant."];
% cervena linka: median
% modry box: mezi kvartilove rozpeti
% cerne linky: data nepovazovana za outliers
figure;
boxplot(vzorky_all, 'labels', jmena_metod);
title("Boxplot výsledků integračních metod")

%% Histogramy

figure;
hold on
for i=1:size(vzorky_all, 2)
    vzorek_now = vzorky_all(:, i);
    histogram(vzorek_now);
end
box on
grid on
title("Rozdělení výsledků integračních metod")


%% Statisticka analyza
% mozna dalsi analyza:
%   test normality vysledku: dovoluje dalsi testovani
%   test rovnosti rozptylu: moznost urcit metodu s nejnizsim rozptylem


%% Funkce

function ZobrazeniZadani(zadani)
%Vykresleni integrovane funkce v zadane oblasti

x_plot = zadani.a:0.01:zadani.b;
y_plot = zadani.f(x_plot);

plot(x_plot, y_plot, 'red', 'linewidth', 2);

xlim([zadani.a, zadani.b])
ylim([0, zadani.c_max])
end

function ZobrazeniHlavniCasti(z_integ, z_hlc)

x_plot = z_integ.a:0.01:z_integ.b;
y_plot = z_hlc.g(x_plot);

hold on
plot(x_plot, y_plot, ': black')
hold off
end

function ZobrazeniRelevantniVyber(z_integ, z_vyb)

x_plot = z_integ.a:0.01:z_integ.b;
y_plot = z_vyb.p(x_plot);

hold on
plot(x_plot, y_plot, '-. black')
hold off
end

function ZobrazeniIntervalu(z_integ, z_inter)

hold on
for i = 1:numel(z_inter.intervaly)
    x = z_inter.intervaly(i);
    plot(x * [1, 1], [0, z_integ.c_max], '-- black')
end
hold off
end
