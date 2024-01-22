%Model bodoveho zdroje zareni
close all
clear variables
clc

% uvodni energie castic, uvazujeme pouze jeden typ emitovanych castic
E0 = 1;
% materialova konstanta pro prostredi a pro uvodni energii castic
% obecne je funkci energie castic
mu0 = 1;

% poloha bodoveho zdroje
X0 = [0, 0, 0];

% pocet modelovanych castic
N = 10;

% uvodni poloha pro vechny castice
X0 = repmat(X0, N, 1);

%% Uvodni emise zdroje
% rovnomerny smer ve 3D: izotropni
V1 = RandSmer(N);
% exponencialne rozdelena volna draha, zavisla na materialove konstante
L1 = RandDelka(N, mu0);
% nove polohy castic
X1 = X0 + V1 .* L1;

% vykresleni
figure
hold on
DrahaPlot(X0, X1, {'green'})
BodyPlot(X1, {'. blue'})
BodyPlot(X0, {'o red', 'MarkerFacecolor', 'red'})
hold off

title('Emise zdroje')

axis equal
grid on
box on

%% Interakce s prostredim
% na konci volne drahy castice interaguje s prostredim

% naivni interakce:
%   interakci "stara" castice zanika a vznika jedna "nova"
%   energie "nove" castice se nemeni od "stare"
%   novy smer je rovnomerne rozdeleny

% energie novych castic: stejna
E1 = E0;

% materialova konstanta pro novou energii
% obecne by mela by funcki nove energie E1
mu1 = mu0;

% nove smery: rovnomerne rozdelene
V2 = RandSmer(N);

% nove volne drahy: zavisle na nove materialove konstante
L2 = RandDelka(N, mu1);

% poloha na konci volne drahy
X2 = X1 + V2 .* L2;

% vykresleni
figure
hold on
DrahaPlot(X0, X1, {'green', 'linewidth', 1})
DrahaPlot(X1, X2, {'yellow', 'linewidth', 1})
BodyPlot(X1, {'. blue'})
BodyPlot(X2, {'. magenta'})
BodyPlot(X0, {'o red', 'MarkerFacecolor', 'red'})
hold off

title('Trajektorie s interakcí')

axis equal
grid on
box on

%% Mozne rozsireni
%   hranice systemu: zdi, ve kterych castice zanikaji
%   spravna interakce: fyzikalne relevantni interakce, zmena energie
%   detektor: terc, ve kterem jsou castice detekovany
%   kolimace: usmerneni zdroje nebo detektoru
%   vicero typu emitovavych castic
%   vicero typu interkaci

%% Funkce

function R = RandDelka(N, mu)
%Exponencialne rozdelene delky s danou stredni hodnotou.
R = rand(N, 1);
R = -(1./mu) .* log(R);
end

function R = RandSmer(N)
%Generovani rovnomerne rozdeleneho smeru ve 3D.
R = randn(N, 3);
N = sqrt(sum(R.^2, 2));
R = R./N;
end

function BodyPlot(X, setting)
%Vykresleni bodu ve 3D pomoci pole.
plot3(X(:, 1), X(:, 2), X(:, 3), setting{:})
end

function DrahaPlot(X1, X2, setting)
%Vykresleni usecek ve 3D zadanych koncovymi body.
plot3(...
    [X1(:, 1), X2(:, 1)]',...
    [X1(:, 2), X2(:, 2)]',...
    [X1(:, 3), X2(:, 3)]',...
    setting{:})
end
