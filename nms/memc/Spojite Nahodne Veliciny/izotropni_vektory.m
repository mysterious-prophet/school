%Predstaveni generovani nahodnych izotropnich vektoru

close all
clear variables
clc

% velikosti vzorku
dims = [1000, 1];

%% Izotropni vektory
% jedna se o vektory v R^n prostru s rovnomerne rozdelenych smerem
% generovany jsou jako roznomerne rozdelene body na n-dimenzionalni jednotkove sfere
% slouzi pro vytvareni nahodnych smeru


%% 1D
% 1D hypersfera jsou dva body -1, 1

% 1D smery jsou pouze "leva" a "prava" = {-1, 1}
% generuje se jako vyvazeny hod minci
smer_1D = rand(dims) < 0.5;

% obrazek
figure;
histogram(smer_1D)
title('1D směry: levá, pravá')


%% 2D
% 2D hypersfera je kruznice
% lze ji popsat pomoci uhlu alpha v intervalu (0, 2*pi)
% vytvoreni x a y souradnice bodu na kruznici pomoci sin a cos funkci

% generovani uhlu
alpha = rand(dims) * 2*pi;
% souradnice
x2D = cos(alpha);
y2D = sin(alpha);

% obrazek
figure
plot(x2D, y2D, '. black')
title('Rovnoměrně rozdělené náhodné body na kružnici')
% nastaveni totozneho meritka pro souradne osy
axis equal


%% 3D
% 3D hypersfera je sfera, sfera je plast koule, koule je vyplnena sfera

% nutnost generovat pomoci spravne transformace
% skriptum str. 52

% generovani dvou velicin
% r 1 ~ U(-1, 1)
r_1 = rand(dims) * 2 - 1;
% r 2 ~ U(0, 2*pi)
r_2 = rand(dims) * 2 * pi;

% souradnice dle transformace
x3D = sqrt(1 - r_1.^2) .* sin(r_2);
y3D = sqrt(1 - r_1.^2) .* cos(r_2);
z3D = r_1;

% obrazek
figure;
% vykresleni bodu do 3D prostoru
plot3(x3D, y3D, z3D, '. black')
title('Rovnoměrně rozdělené náhodné body na sféře')
axis equal


%% ND
% moznost vyuziti vlasnosti normalniho rozdeleni
% pro vektory X = (X_1, ..., X_N), X_i ~N(0, 1) plati, ze
% X/||X|| je rovnomerne rozdeleny vektor na ND hypersfere
% ukazka pro 3D:

% definice dimenze
N = 3;
% generuji N-tice z N(0, 1);
X = randn([dims(1), 3]);
% vypocet normy vektoru
% norma je odmocnina se souctu kvadratu souradnic
normX = sqrt(sum(X.^2, 2));
% vydeleni vektoru jejich velikosti, vznikani vektory velikosti jedna
% vektory velikosti jedna lezi na sfere s polomerem jedna
uX = X ./ normX;

% obrazek
figure;
% vykresleni bodu do 3D prostoru
plot3(uX(:, 1), uX(:, 2), uX(:, 3), '. black')
title('Rovnoměrně rozdělené náhodné body na sféře, obecný postup')
axis equal
