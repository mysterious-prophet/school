%Predstaveni zakladni MATLAB syntaxe

% zavreni vsech MATLAB otevrenych figur(oken)
close all
% vymazani vsech promenych z Workspace
clear variables
% vymazani prikazu z konzole
clc


%% Promenne

% neni potreba specifikovat datovy typ
% strednik zabranuje vypsani radku na konzoli
a = 5;
% volani beznych funkci
s = sin(a);
c = cos(a);
e = exp(a);
lg = log(a);
lg10 = log10(a);


%% Pole

% skoro vsechno v MATLABUu je pole
% skalarni promenna je pole 1x1
% velikost pole (vysledek je videt ve workspace)
size_a = size(a);
% rucni vytvoreni pomoci [], carek a stredniku
% radkove pole 1x3
A = [1, 2, 6];
% sloupcove pole 4x1
B = [4; 3; 5; 1];
% pole 2x3, tri tecky zalomuji radek pro prehlednost
C = [3, 8, 9;...
    7, 6, 5];
% slovo je pole znaku vcetne mezer
slovo = 'MMC je nejlepsi';
% velikost
size_slovo = size(slovo);


%% Zakladni pole

% pouziti funkci pro vytvoreni pole
% pole nul velikosti 2x3, rozmery predavam jako pole
N = zeros([2, 3]);
% pole jednicek: obdobna syntax jako u zeros
J = ones([5, 2]);
% pole libovolnych konstant: pole osmicek
% jeden parametr vytvari ctvercovou matici
D = 8 * ones(2);
% pole "not a number" hodnot
E = nan([3, 8]);  
% jednotkova matice
I = eye([3, 4]);
% posloupnost s kontantnim krokem
% zacimane od nuly, a jdeme po dvou az do dvaceti
P = 0:2:20;
% pokud vynechame krok, pak je krok 1
P2 = 1:100;


%% Indexovani

% pole o d dimenzich indexujeme d indexy
% nacteme prvek z pole
n11 = N(1, 1);
% prepiseme prvek v poli
% v konzoli pak muzeme prekontrolovat vysledek
N(2, 3) = 69;
% index muze odkazovat na vice elementu
% nacteme 2. a 3. prvek najednou
% index je nyni pole [2, 3]
p23 = P([2, 3]);
% nacteni 2. az 50. prvku
% index je [2,3, 4, ..., 50]
% index vytvorime pomoci 2:50
% syntax 2:50 vytvari pole, neni treba pridavat []
p2az50 = P2(2:50);
% pokud chceme vybrat vse v 1. radku
I_radek1 = I(1, :);
% pokud chceme vybrat vse v 2. sloupci
I_sloupec2 = I(:, 2);
% pokud chceme z vicerozmerneho pole udelat pole 'hodne' krat jedna
nudle = I(:);


%% Nahodna cisla

% tri zakladni generatory
% U(0,1): rovnomerne rozdeleni na intervalu (0, 1)
% jen zadame velikost vysledneho pole (jako u zeros)
r = rand([10, 100]);
% N(0, 1): standardni normalni rozdeleni
r_normal = randn([1, 1000]);
% rovnomerne na mnozine cisel {1, 2, ..., 666}, kazde s pravd. 1/666
% nejdrive zadame max cislo, pak rozmer vysledneho pole
r_integer = randi(666, [8, 99]);


%% Funkce poli

% soucet kazdeho sloupce
sum_I = sum(I);
% soucet vsech prvku v poli
total_sum_I = sum(I(:));
% prubezny soucet: n-ty prvek je soucet 1:n prvku
sc_rada = cumsum(1:10);
% produkt vsech prvku
total_prod_I = prod(I(:));
% prumer v kazdem sloupci
r_mean = mean(r);
% prumer z celeho vicerozmerneho pole
r_mean_total = mean(r(:));
% median (jako mean)
r_median_total = median(r(:));
% rozptyl
r_var = var(r);
% standartni odchylka = odmocnina z rozptylu
r_std = std(r);
% empiricky kvantil
% polovicni kvantil je median
total_q_05 = quantile(r(:), 0.5);


%% Obrazky

% vytvorim nove okno kam budu kreslit
figure;
% histogram vsech dat v poli
histogram(r)
% popisek obrazku
title('Histogram U(0, 1)')
% popisek osy x
xlabel('hodnoty')
% popisek osy y
ylabel('cetnosti')

% vykresleni cary sin(x)
% jako x si nakrokuji interval 0 az 2*pi
x = 0:0.01:(2*pi);
% funcke sin aplikovana na kazdy prvek
y = sin(x);
% vytvorim nove okno (nechci prekreslit histogram)
figure;
% kreslim caru
plot(x, y);
% pridam mrizku
grid on
% popisek obrazku
title('Funkce sinus')
% popisek osy x
xlabel('x')
% popisek osy y
ylabel('y')

% vicero car najednou
% definuji cary
x2 = 0:0.01:1;
y1 = exp(x2);
y2 = cos(x2);
figure;
% reknu oknu ze ma pockat nez pridam vsechny cary
hold on
% dve cary s formatovanim
plot(x2, y1, 'red')
plot(x2, y2, 'black')
% dokresleno, muzu pustit
hold off
% legenda
% popsiky porade v {}
legend({'exp', 'cos'})
% popisky
title('Porovnani funkci')
xlabel('x')
ylabel('y')
% pridam mrizku
grid on
% pridam ramecek
box on


%% QQplot

% pole nahodnych hodnot N(0, 1)
r_norm = randn([10000, 1]);
figure;
% sledujeme chvosty
qqplot(r_norm);
% pridat ramecek a mrizku
box on
grid on
% udelam histogram
figure; histogram(r_norm);
