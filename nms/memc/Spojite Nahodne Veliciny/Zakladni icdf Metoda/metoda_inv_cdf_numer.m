%Ukazka zakladni metody s inverzni distribucni funkci s numerickym resenim
% jako uvod k numerickemu reseni rovnic slouzi soubor 'numericke_reseni.m'

close all
clear variables
clc

% velikost poli
dims  = [1000, 1];


%% Generuji z U(0, 1)

r = rand(dims);


%% Exponencialni rozdeleni

exp_pdf = @(x, lam) lam * exp(-lam * x);
% zvolena hodnota parametru
my_lam = 4;
% (predstirame ze) neni mozne nalezt predpis inverzni cdf


%% Numericky nalezena icdf

% reseni ve funckci exp_icdf_numeric (na konci souboru)
% funkci nelze aplikovat na cele pole 'r' najednou: volame v cyklu
exp_x = nan(size(r));
% numel: number of elements
for i = 1:numel(exp_x)
    exp_x(i) = exp_icdf_numeric(r(i), my_lam);
end

%% Vykresleni
x_plot = 0:0.01:2;
y_plot = exp_pdf(x_plot, my_lam);
figure;
histogram(exp_x, 'Normalization', 'pdf');
hold on
plot(x_plot, y_plot, 'red', 'Linewidth', 2)
hold off


%% Funkce

function x = exp_icdf_numeric(y, my_lam)
%Inverzni cdf exponencialniho rozdelelni

% znama cdf
exp_cdf = @(x, lam) 1 - exp(-lam * x);
% vlozeni parametru
f = @(x) exp_cdf(x, my_lam);
% reseni pro f(x) = y <=> g(x) = 0, g(x) = f(x) - y
g = @(x) f(x) - y;
% uvodni odhad
x0 = 0.5;
% hledani numerickeho reseni
x = fzero(g, x0);
end
