function[koren, i] = regulaFalsi

%nadefinujeme f(x) a budeme hledat reseni f(x)=0
f=inline('exp(x)-6');

a=0; % pocatecni body omezujici reseni x(i)
b=5; % a x(i+1)

reseni = []; % aktualni odhad reseni

%nespravne inicialni odhady intervalu
if f(a)*f(b)>0
    return
end

%jinak je mozno pocitat
i = 1;
tolerance = 10e-6;
%protoze regula falsi muze konvergovat pomalu, zdalo se mi lepsi prepsat tohle
%tak,ze nebude predem dany pocet iteraci, ale chyba kterou tolerujeme
while 1
    %odvozeny vzorec
    c=(a*f(b)-f(a)*b)/(f(b)-f(a));
    %je-li koren v jednom z danych podintervalu zmen meze a presun se na dany
    %podinterval
    if f(a)*f(c)<0   
        b = c;
    else
        a = c;
    end
    %zaznam o resenich
    reseni(i)=c;
    %ukoncovaci podminka
    if(abs(f(c))<tolerance)
        break
    end
    i = i+1;
end

koren=reseni(end) % odhad konecneho reseni

% zobrazime vyvoj reseni v zavislosti na iteracich vlevo
plot(1:length(reseni),reseni);
title('Vyvoj reseni');
xlabel('iterace');
ylabel('reseni');

end