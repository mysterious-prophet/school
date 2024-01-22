%Prehled rizeni kodu
% if, for, while, switch, warning , error


%% Podminky

% if a logicka hodnota
a = 5;
if a >= 2
    % vykonani pokud je podminka true
    disp('true')
else
    % vykonani pokud je podminka false
    disp('false')
end


%% Cykly

% for cyklus
% priklad:
for i = 1:5
    disp(i)
end
% for cyklus prochazi pole hodnot, v tomto pripade je pole 1:5
% n-tem cyklu je v promene i n-ta hodnota z pole 1:5

% vycistim konzoli
clc

% obecnejsi priklad:
moje_pole = 2:2:8;
for i = moje_pole
    disp(i)
end

% vymazu z konzole predchozi vypis
clc

% while cyklus
% priklad
i = 1;
while i <= 5
    disp(i)
    i = i + 5;
end

clc

% preruseni cyklu pomoci break a continue
% continue preskoci soucasny krok:
for i = 1:4
    if i == 2
        continue
    else
        disp(i)
    end
end

clc
% break ukonci cely cyklus
for i = 1:8
    if i == 6
        break
    end
    disp(i)
end


%% Switch

% vybirani z mnoha moznosti
slovo = 'noha';
switch slovo
    case 'noha'
        disp('nohavice')
    case 'hlava'
        disp('hlavice')
    case 'zada'
        disp('zadnice')
    case {'pijak', 'pijano'}
        % tento case nastane pro dve moznosti
        disp('pijavice')
            
    otherwise
        % tento pripad nastane pokud zadana promenna neodpovida zadnemu
        % pripadu
        disp('Toto slovo neznam.')
end

clc


%% Warning a error

% warning pro upozorneni na nestandardni pripad, neukonci program
warning('Pozor, pozor!')
% error pro hlaseny chyby, ukonci program
error('Velky spatny!!!')
