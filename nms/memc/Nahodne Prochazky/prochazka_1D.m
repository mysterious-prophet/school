%Jednorozmerna nahodna prochazka
close all
clear variables
clc

% Pohybujici se castice/agent pro realne ose
% Pozice castice v casovem kroku je urcena 1D hodnotou = jednim cislem.
% Nova pozice je rovna stare pozici plus nahodny posun.
% Nahodny smer posunu -1/+1 oznacen r.
% Delka posunu oznacena d.
% x_{t+1} = x_{t} + r * d,
% Pr(r  = 1) = p , p \in(0, 1),
% Pr(r  = -1) = 1 - p.
% Nahodne posuny jsou na sobe nezavisle.
% Uvodni poloha castice je 0.
% Pohyb dvou a vice casti je na sobe vzajemne nezavisly.

%% Parametry
% pocet simulovanych casovych kroku
T = 1000000;
% pocet castic
N = 10;
% pravdepodobnost pohybu do plusoveho smeru
p = 0.5;
% delka kroku
d = 1;

%% Casovy vyvoj polohy castic
% % souradnice kazde castice v casovych krocich
% X = nan(N, T);
% % v prvnim kroce jsou vsechny castice v nule
% X(:, 1) = zeros(N, 1);
% % casovy vyvoj
% for t = 2:T
%     % nahone hodny U(0, 1)
%     r = rand(N, 1);
%     % rozhodnuti leva/prava <=> 0, 1
%     r = r < p;
%     % transformace -1, 1
%     r = 2 * r -1;
%     
%     % nahodny posun pristen k predchozi poloze
%     X(:, t) = X(:, t - 1) + r * d;   
% end

% alternativni implementace
% vektorizovano, optimalizace pro MATLAB
R = rand(N, T-1) < p;
R = 2 * R - 1;
R = R * d;
% cumsum: kumulativni suma, R_k = sum_{i=1}^k r_i
R = cumsum(R, 2);
X = [zeros(N, 1), R];

%% Vykresleni trajektorii
figure
plot(X', '.')
title('Trajektorie částic')
xlabel('časový krok')
ylabel('poloha')

%% Vykreseleni vzdalenosti dvou castic
if N > 1
    D = X(1, :) - X(2, :);
    figure
    plot(D, '.')
    title('Vzdálenost dvojice částic')
    xlabel('časový krok')
    ylabel('vzdálenost')
end

%% Vykresleni teziste castic
% castice maji stejnou hmotnost / vahu
% teziste je prumer souradnic
teziste = mean(X);

figure
plot(teziste, '.')
title('Trajektorie těžistě částic')
xlabel('časový krok')
ylabel('poloha')

%% Vykresleni rozptylu castic
% roztyl souradnic castic v kazdem casovem kroce
rozptyl = var(X);
figure;
plot(rozptyl, '.')
title('Roztyl částic')
xlabel('časový krok')
ylabel('hodnota rozptylu')
