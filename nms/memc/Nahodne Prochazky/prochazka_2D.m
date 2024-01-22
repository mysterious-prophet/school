%Nahodna prochazka v 2D
close all
clear variables
clc

% Implmentace provedena vektorizovane pro optimalizaci v MATLAB.

%% Parametry
% pocet castic
N = 1000;
% pocet casovych kroku
T = 1000;

% mozne vektory posunu
V = [...
    0, 1;
    1, 0;
    0, -1;
    -1, 0;
    ];
% pocet vektoru posunu
numV = size(V, 1);

% zvolme pravdepodobnosti posunu
% kazdy vektor ma svoji pravdepodobnost
% soucet musi byt roven jedne

% volime rozmonerne
p = ones(numV, 1);
% normalizace
p = p/sum(p);

%% Generovani trajektorii
% v kazdem kroku pro kazdou castici je nahodne zvolen vektor posunu
% pro volbu vektoru staci urcit jeho index v poli V

% celkem je potreba N krat (T - 1) voleb nahodnych posunu
% nahodne jsou generovany indexy vektoru posunu dle pravdepodobnosti v poli p
idxV = randsample(1:numV, N*(T - 1), true, p);

% pomoci indexu jsou vybrany plne vektory posunu
allV = V(idxV, :);
% zmena tvaru pole pro rozdeleni vektoru do N skupin
% kazda skupina urcuje posuny jedne castice
allV = reshape(allV', 2, N, T - 1);

% kumulativni suma pro secteni posunu v kazde souradnici
% kumulativni secteni pres dimenzi odpovidajici casu
cumV = cumsum(allV, 3);

% pridani uvodni pozice [0, 0] pro vsechny castice
X = cat(3, zeros(2, N, 1), cumV);

%% Vykresleni trajektorie jedne castice
% vykresleni trajektorie prvni castice

% souradnice trajektorie
x_now = X(1, 1, :);
y_now = X(2, 1, :);

% uprava dimenzi poli: dimenze o veliksoti 1 "jdou na konec"
x_now = squeeze(x_now);
y_now = squeeze(y_now);

% vykresleni
figure
plot(x_now, y_now, '.-')
title('Trajektorie částice')
axis('equal')

%% Vykresleni teziste castice
% teziste je prumer: vsechny catice maji stejnou vahu
teziste = mean(X, 2);

% souradnice teziste
x_now = teziste(1, 1, :);
y_now = teziste(2, 1, :);

% uprava dimenzi poli: dimenze o velikosti 1 jdou na konec
x_now = squeeze(x_now);
y_now = squeeze(y_now);

% vykresleni
figure
plot(x_now, y_now, '.-')
title('Trajektorie těžiště částic')
axis('equal')

%% Vykresleni vzdalenosti teziste od pocatku
% euklidovska vzdalenost teziste od pocatku = velikost vektoru
vzdalenost = sqrt(sum(teziste.^2, 1));
% uprava poradi dimenzi pole
vzdalenost = squeeze(vzdalenost);

figure
plot(vzdalenost)
xlabel('časový krok')
ylabel('vzdálenost')
title('Vzdálenost těžiště částic od počáteční polohy')

%% Vykresleni histogramu polohy castic v poslednim casovem kroce
x_now = X(1, :, end);
y_now = X(2, :, end);
figure
histogram2(x_now, y_now)
title('Rozdělení polohy částic na konci simulace')

%% Vykresleni vyvoje trajektorie vsech castic
% vykresleni jako animace

% otevreni okna
% f je "ukazatel" na okno, do ktereho ma byt kreleno 
f = figure;
% vytvoreni souradne soustavy uvnitr okna
gca;
for t = 1:T
    % vykresleni i teho casoveho kroku
    
    % x souradnice vsech souradnic
    x_now = X(1, :, t);
    % x souradnice vsech souradnic
    y_now = X(2, :, t);
    % vykresleni do zvolenoho okna 'f'
    plot(f.Children(1), x_now, y_now, 'o blue')
    
    % ukotveni rozmeru os zvoleneho okna
    xlim(f.Children(1), [-100, 100])
    ylim(f.Children(1), [-100, 100])
    % popisek obrazku
    title(f.Children(1), "Časový vývoj pohybu částic, T = " + t)
    % nastaveni os
    axis(f.Children(1), 'equal', 'off')
    
    % pozastaveni v sekundach
    pause(0.1)
end

%% Poznamky
%   Pri implemntaci bez uziti vektorizace (prace s vicerozmernymi poli) je
%   vyssi slozitost kodu. V takovemto pripade je mozne implmentovat funkci
%   pro vytvoreni trajektorie jedne castice, krajektorie ukladat do např.
%   pole bunek a pote vykteslovat a pocitat tratistiky (teziste) v cyklu
%   prochazejici jednotlive trajektorie.
%
%   Volba moznych vektoru posunu urcuje na jake pomyslne mrizce se castice
%   pohybuji. Jejich zmenou je mozne nastavit pohyb po ctvercove,
%   trojuhelnikone nebo sestiuhelnikove mrizce.
%
%   Uprava kodu pro vytvareni nahodne prochazky v D-dimenzionalnim prostoru
%   je prosta, pokud se upravi dimenze poli a vektoru posunu. Pro
%   vykreselni trajektorii ve 3D je mozne poziti funkci plot3.