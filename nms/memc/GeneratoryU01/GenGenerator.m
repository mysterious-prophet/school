function r = GenGenerator(dims, generatorName)
%Generovani nahodnych cisel z U(0, 1)
%
%   r = GENGENERATOR(dims, generatorName) vygeneruje pole o velikosti dims
%   s nahodnymi hodnotami z U(0, 1) pomoci generatoru urceneho pomoci
%   generatorName
%
%   dims ... rozmer vystupniho pole
%   generatorName ... oznaceni geenratoru
%   r ... vysledne pole s nahodnymi cisly z U(0, 1)

arguments
    dims (:, :) {mustBeInteger, mustBePositive}
    generatorName (1, 1) string
end


% zvoleni generatoru
switch generatorName
    case 'square'
        r = GeneratorSquare(dims);
    case 'gen50'
        r = Generator50(dims);
    case 'randu'
        r = GeneratorRandu(dims);
    otherwise
        error('Neznamy generator.')
end
end

function xn1 = LinKong(xn, K, B, M)
%Linearni kongruencni generator

xn1 = mod(K * xn + B, M);
end

function r = Generate(dims, seed, generator)
%Vytvoreni velkeho mnozstvi cisel pomoci generatoru

% vytvoreni prazdneho pole
r = nan(dims);
% pouziti vstupniho seed
r(1) = generator(seed);

% generovani pseudonahodne rady
% numel: numer of elements
for i = 2:numel(r)
    r(i) = generator(r(i - 1));
end
end

function seed = GetSeed()
%Ziskani seedu pro generatory pomoci casu

% ziskani data a casu
c = clock;
% posledni hodnota jsou sekundy s presnosti na milisec.
c = c(end);
% ziskani poctu milisekund: hodnoty 0 az 999
seed = (c - floor(c)) * 1000;
% zajisteni celociselnosti
seed = floor(seed);
end

function r = Generator50(dims)
%Generator z malych pocitacu z poloviny minuleho stoleti
% Skriptum str. 66

% definuji parametry generatoru
K = 23;
B = 0;
M = 10^8 + 1;

% vytvoreni generovaci funkce, z x_{n} vytvori x_{n+1}
% dosazeni parametru do linearniho kongurencniho generatoru
GenFun = @(xn) LinKong(xn, K, B, M);

% ziskani seedu ze soucasneho casu
seed = GetSeed();

% generovani
r = Generate(dims, seed, GenFun);

% normovani na (0, 1)
r = r/M;
end

function r = GeneratorRandu(dims)
%Randu generator
% Skriptum str. 67

% parametry
M = 2^31;
K  = 65539;
B = 0;

% vytvoreni generovaci funkce
% dosazeni parametru do linearniho kongurencniho generatoru
GenFun = @(xn) LinKong(xn, K, B, M);

% ziskani seedu ze soucasneho casu
seed = GetSeed();
% metoda vyzaduje lichy seed
if mod(seed, 2) == 0
    % pokud je zbytek po deleni dvema nula, pak je seed sudy
    % upravim seed na liche cislo
    seed = seed + 1;
end

% generovani
r = Generate(dims, seed, GenFun);

% normovani na (0, 1)
r = r/M;
end

function r = GeneratorSquare(dims)
%Middle-square methoda
% https://en.wikipedia.org/wiki/Middle-square_method

% pocet cifer generovaneho celeho cisla
N = 12;

% seed musi byt cislo s N ciframi
% GetSeed vraci cisla 0, 999
seed = GetSeed();
% umocnit na N/3 aby vznilo cislo z dost. poctem cifer
seed = seed^(N/3);

% vybrani prostrednich N cifer z druhe mocniny
GenFun = @(xn) mod(floor((xn^2) / 10^(N / 4)), 10^N);

% genrovani
r = Generate(dims, seed, GenFun);

% normovani na (0, 1)
r = r/(10^N);
end