%Funkce

close all
clear variables
clc


%% Anonymni funkce

% funkci si definuji na jednu radku
% funkce se chova jako promenna a je ve Workspace

% funkce druha mocnina
% x je promena
kvadrat = @(x) x * x;
% zavolam funkci
asi_ctyri = kvadrat(2);

% funkce s vicero parametry
% nekolikanasobek
nasob = @(n, x) n * x;
% zavolam
asi_sest = nasob(3, 2);
% novou funkci mohu vytvorit pomoci existujici
petinasobek = @(x) nasob(5, x);


%% Funkce na konci souboru

% na konci souboru je mozne definovat funkce
% tyto funkce lze volat pouze v danem souboru
% nelze je volat z prikazove radky

% zavolam funkci Dvojnasobek z konce tohoto souboru
asi_dvanact = Dvojnasobek(6);


%% Funkce v souborech

% vytvorime novy soubor
% hlavicka "function y = jmeno_funkce(par1, par2)"
% soubor se musi jmenovat stejne jako funkce
% soubor s funkci musi byt ve stejne slozce, aby sla funkce zavolat

% koukneme na prilozenou funkci Trojnasobek
% kdyz nahledeneme do souboru, uvidime format komentaru
% vidime, ze i v souboru s funkci je mozne na konec pridat funci
% koukneme co funkce dela = zavolame help
% do konzole se vypise komentar k funkci
help Trojnasobek
% zavolame
asi_devet = Trojnasobek(3);


%% Funkce

function y = Dvojnasobek(x)
%Zdvojnasobeni vstupni hodnoty

% vynasobim dvema
y = 2 * x;
end
