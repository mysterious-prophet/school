function vlcislo

% vypocet nejvetsiho vlastniho cisla

% pouzijeme velmi jednoduchou diagonalni matici 3x3, u ktere zname vlastni cisla, 
% ale muzete si vyzkouset i jine matice

%matice=[4 0 0;0 3.7 0; 0 0 3]
matice=[4 0 -10;0 3.7 -8.8; -7.85 2.6 3]

% do vlastniho vektoru v ulozime uvodni odhad

v=[1;1;1]

% budeme opakovat 50, v prubehu vypoctu si budeme pamatovat normu matice*v, 
% tedy odhad vlastniho cisla (vime ze se ma blizit ctyrce)

iteraci=50;

for i=1:iteraci
	odhadVlastnihoCisla(i) = norm(matice*v);
	v = matice*v / norm(matice*v);
end;

% odhad vlastniho cisla je
lambda=norm(matice*v)

% odhad vlastniho vektoru je
v

% zobrazime si jak jsme se k vlastnimu cislu blizili

plot(1:iteraci,odhadVlastnihoCisla);

end