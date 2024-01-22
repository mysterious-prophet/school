%Metropolisuv algoritmus pro symetricke retezce
close all
clear variables
clc

%% Definice ulohy
% maximalizovana funkce
% dva gausovske peaky
g = @(x, y, Sx, Sy) exp(-(x-Sx).^2 -(y-Sy).^2);
f = @(x, y) g(x, y, 0, 0) + 0.5*g(x/10, y/10, 1, 1);

%% Definice metody
% uvodni poloha trajektorie
X0 = [5, 5];
% delka kroku
d = 0.1;
% parametr metody
% urcuje zamitaci/prijimaci pravdepodobnost novych stavu
lam = 10;
% pocet casovych kroku trajektorie
N = 100000;

%% Generovani trajektorie retezce
[T, F] = GetTraj(f, N, lam, X0, d);

%% Vykresleni trajektorie
% limity vykreslovane plochy
limx = [min(T(:, 1)), max(T(:, 1))];
limy = [min(T(:, 2)), max(T(:, 2))];

figure
hold on
% body trajektorie
scatter(T(:, 1), T(:, 2), 1, F, '.')
% vykresleni krivek propojujici body se stejnou funkcni hodnotou
fcontour(f, [limx, limy]);
% vykresleni lokalnich maxim
plot(0, 0, 'x red', 'MarkerSize', 20);
plot(10, 10, 'x red', 'MarkerSize', 20);
hold off
% skryti os a nastaveni meritka os
axis equal off
% limity os
xlim(limx)
ylim(limy)
% popisek obrazku
title("\lambda = " + lam)

%% Funkce
function [T, F] = GetTraj(f, N, lam, X0, d)
%Vytvoreni trajektrie

% vytvoreni modelu
model = GetModel(X0, d, lam, f);
% pole pro zapis trajektorie
T = nan(N, 2);
% pole pro zapis ohodnoceni stavu v trajektori
F = nan(N, 1);
% ulozeni uvodniho stavu
T(1, :) = X0;
F(1) = f(X0(1), X0(2));

% casove kroky
for t = 2:N
    % vyvoj modelu o jeden krok
    model = Update(model);
    % ziskani noveho stavu
    T(t, :) = model.X;
    % ziskani ohodnoceni stavu
    F(t) = model.fval;
end
end

function model = GetModel(X0, d, lam, f)
%Vytvoreni modelu

% ulozeni parametru do struktury

% delka kroku
model.d = d;
% stav systemu
model.X = X0;
% parametr zamitaci/pripousteci pravdepodobnosti
model.lam = lam;
% funkce ohodnocujici stavy
model.f = @(x) f(x(1), x(2));
% ohodnoceni uvodniho stavu
model.fval = model.f(model.X);
end

function model = Update(model)
%Vykonani jednoho kroku modelu

% nejprve je proveden vyber noveho stavu
% novy stav vybran z nahodne prochazky
% nahodne je zvolen uhel
a = rand * 2*pi;
% je vytvoren vektor posunu, delka vektoru urcena jako parametr modelu
v = [cos(a), sin(a)] * model.d;
% novy stav
Xnew = model.X + v;
% hodnota v novem stavu
fvalnew = model.f(Xnew);

% vypocet pripousteci pravdepdobnosti
pi_old = model.lam^model.fval;
pi_new = model.lam^fvalnew;
p = pi_new/pi_old;
p = min(1, p);

% urceni zda je novy stav zamitnut nebo pripusten
if rand < p
    % stav je pripusten
    % upraveni stavu a hodnoty ve stavu
    model.X = Xnew;
    model.fval = fvalnew;
end
end