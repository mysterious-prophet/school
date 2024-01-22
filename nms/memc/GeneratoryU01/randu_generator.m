%Ukazka vlastnosti Randu generatoru
close all
clear varables
clc

% velikost nagenerovaneho pole
dims = [3, 10000];

%% Generovani nahodnych hodnot pomoci Randu
r = GenGenerator(dims, 'randu');

% histogram nagenerovanych hodnot
figure;
histogram(r)

%% Animace
% vykresleni trojic hodnot do krychle (0, 1) x (0, 1) x (0, 1)
% s obrazkem bude rotovano
% sledujeme jestli jsou body rozmisteny rovnomerne

% otevreni okna s bilym pozadim
figure('Color', 'white');
% vykresleni bodu
plot3(r(1, :), r(2, :), r(3, :), '. black')
% nastaveni chovani os
% equal: jednotne meritko vsech os
% off: osy nejsou rozbrazeny
% vis3d: ukotveni velikosti os pri rotovani
axis equal off vis3d

% rotovani v krocich animace
for i=1:1050
    % pootoceni os pri rotaci o 'i' stupnu
    view(i, i)
    % pozastaveni o pocet sekund pro ukazku soucasneho pootoceni
    pause(0.02)
end
