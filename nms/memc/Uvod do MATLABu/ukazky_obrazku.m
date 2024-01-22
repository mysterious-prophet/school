% Ukazka pokrocile prace s grafy

close all
clear variables
clc


%% Uvodni poznamka

% MATLAB ma siroke spektrum nastroju na vykreslovani dat.
% Vykrelseni spocina ve vytvoreni grafickeho obejktu, ktery je vlozen do
% os, ktere jsou v okne (figure)
% Osy se bezne tvori automaticky pri vlozeni grafickeho obejktu do okna.


%% Minimalni obrazek

% Vykresleni prubehu funkce.

% vytvorime data, která chceme kreslit
x = 0:0.01:10;
s = sin(x);
c = cos(x);

% vytvorime nove okno do kteroho budeme kreslit
% abychom s oknem mohli dale pracovat ulozime si na nej "handle"
% handle je pomyslny ukazatel, pres ktery muzeme upravovat dany objekt

f = figure;
% chceme upravit vnitrni atributy objektu
f.Name = "jmeno okna";
% pokud do prikazoveho okna zadame 'f', pak se nam ukazou dostupne atributy

% chci zmenit velikost okna
% chci ulozit pozici okna
% pole 4 elementu [polohaX, polohaY, velikostX, velikostY]
% nejprve nastavim jednotky
f.Units = "centimeters";
% ziskam pozici
pozice = f.Position;
% upravim pouze velikost okna, ne umisteni
% chci 10x15 cm okno
pozice([3, 4]) = [20, 10];
% nastavim noovu velikost
f.Position = pozice;


% vytvozine objekt 'plot', ktery bude predstavovat caru
% opet si vytvarime handle
hp1 = plot(x, c, "red");
% upravime atribut
hp1.LineWidth = 2;

% pokud bychom pridali dalsi objekt to obrazku, pak bychom prepsali vytorenou caru
% musime 'podrzet' soucasny obrazek, abychom mohli pridavat
hold on
% nyni muzeme pridava tdalsi graficke objekty bez prepsani predchozich
hp2 = plot(x, s, "blue");
% upravime atribut
hp2.LineStyle = ":";


% muze pridat dalsi prvky, treba popisky os
xlabel("x")
ylabel("y")
% pridani popisku obrazku
ht = title("Popisek obrázku");
% menim hodnotu atributu
ht.FontSize = 8;

% mohu pridat legendu
% nejprve specifikuje k jakym obejktum chci legendu udelat a pote vkladam
% popisky a pote dalsi specifikace
legend([hp1, hp2], ["čára kosinus", "čára sinus"],...
    "Location", "northwest")

% pridavam mrizku
grid on
% vypinam ohraniceni obrazku
box off
% mohu nastavit meritko os
axis equal


%% Ulozeni obrazku
% Pro vkladani obrazku do dokumentu je nutne ho ulozit do souboru.

saveas(f, "muj_obrazek.png")
