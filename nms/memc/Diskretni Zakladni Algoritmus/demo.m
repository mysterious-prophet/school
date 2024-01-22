%Zakladni algoritmus pro diskretni nahodne veliciny a jeho aplikace

% Zpracovano dle:
% Virius, M.: Metoda Monte Carlo. Praha, Vydavatelství ČVUT 2010. ISBN 978-80-01-04595-4
% Strana 24

close all
clear variables
clc

% Kvuli rozdilnosti implementace je nutne oddelit pripady, kdy je
% pravdepodobnost zadana pomoci konecneho vektoru pravdepodobnosti, nebo
% pomoci pravdepodobnostni funkce f(x) = Pr(x = k).

% Nejprve jsou ukazany pripady, kdy je pravdepodobnost dana jako pole
% pravdepodobnosti.
help ZaklAlgDisk_array


%% Priklad: hod minci

% kazda strana ma pravdepodobnost 1/2
% pravdepodobnostni vektor obou stran mince je
p_mince = [0.5, 0.5];
% pro kontrolu statistickych vlastnosti nageneruji N hodnot
N = 100000;
% vytvorim pole kam budu nagenerovane hodnoty ukladat
k_binom = nan([N, 1]);
% v cyklu generuji jednu hodnotu za druhou
for i = 1:N
    % volam funkci s naimplementovanym algoritmem
    k_binom(i) = ZaklAlgDisk_array(p_mince);
end
% vykreslim histogram
figure;
histogram(k_binom);
title('Hod minci')
% alternativni implementace optimalizovana pro MATLAB:
help HodMinci
% MATLAB funkce vhodna pro generovani hodu minci:
% k_mince = randi(2, [N, 1]);


%% Priklad: hod kostkou

% pravdepodobnost 1/6 pro kazdou stenu
p_kostka = ones([1, 6]) /6;
k_kostka = nan([N, 1]);
for i = 1:N
    k_kostka(i) = ZaklAlgDisk_array(p_kostka);
end
figure;
histogram(k_kostka);
title('Hod kostkou')
% alternativni implementace optimalizovana pro MATLAB:
help HodKostkou
% MATLAB funkce vhodna pro generovani hodu kostkou
% k_kostka = randi(6, [N, 1]);

% dale se venujeme prikladum, kdy je rozdeleni dano pravdopodobnostni funkci
help ZaklAlgDisk_function


%% Priklad: binomicke rozdeleni

% pravdepodobnostni funkce jako anonymni funkce
% nchoosek je kombinacni cislo: n nad k
f_binom = @(k, p, n) nchoosek(n, k) * p^k * (1 - p)^(n - k);
% specifikuji parametry: p = 0.5, n = 40
f_binom_spec = @(k) f_binom(k, 0.5, 40);
% vytvorime pole kam budeme nagenerovane hodnoty ukladat
k_binom = nan([N, 1]);
% v cyklu generujeme jednu hodnotu za druhou
for i = 1:N
    % volame funkci s naimplementovanym algoritmem
    k_binom(i) = ZaklAlgDisk_function(f_binom_spec);
end
% vykreslime histogram
figure;
histogram(k_binom);
title('Binomicke rozdeleni')
% MATLAB funkce vhodna pro generovani z binomickeho rozdeleni
% k_binom = binornd(40, 0.5, [N, 1]);


%% Priklad: poissonovo rozdeleni

f_pois = @(k, lam) lam^k / factorial(k) * exp(-lam);
% specifikujeme paramatr lambda: lam = 10
f_pois_spec = @(k) f_pois(k, 10);
% generujeme
k_pois = nan([N, 1]);
for i = 1:N
    % volame funkci s naimplementovanym algoritmem
    k_pois(i) = ZaklAlgDisk_function(f_pois_spec);
end
% vykreslime histogram
figure;
histogram(k_pois);
title('Poissonovo rozdeleni')
% MATLAB funkce vhodna pro generovani z poissonova rozdeleni
% k_pois = poissrnd(10, [N, 1]);
