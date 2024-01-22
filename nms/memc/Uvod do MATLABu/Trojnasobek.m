function y = Trojnasobek(x)
%TROJNASOBEK Vynasobeni vlozeneho cisla trema.
%   y = TROJNASOBEK(x) ulozi do y trojnasobek x
%
%   x ... vstupni hodnota
%   y ... trojnasobek vstupni hodnoty

% vynasobeni trema pomoci pomocne funkce
y = vykonej_vynasobeni_trema(x);
end

function y = vykonej_vynasobeni_trema(x)
% Pomocna funkce pro nasobeni trema

% vynasobeni trema
y = 3 * x;
end
