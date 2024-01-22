function chebyshev

N = 20;  % stupen aproximace (pocet Cebysevovych polynomu)
a = -10; % levy kraj intervalu
b = 10;  % pravy kraj intervalu
zadanafce = @(t)  t.^4 .* log(10+abs(t)) .* cos(t);
%t interval <a,b>
bodu = 1000; % pocet bodu, ze kterych chceme funkci aproximovat


    % transformace intervalu z <a,b> do <-1,1>
    function x=trans(t)
        x = ( 2*t - (a+b) ) / (b-a);
    end

    function func=func(xx) % hodnota funkce pro xx transformovane z <a,b> na <-1,1>
        t = ( xx*(b-a) + (a+b) ) / 2; % "roztahneme" hodnoty z intervalu <-1,1> na <a,b>
        func = zadanafce(t);  % aproximovana funkce
    end

    function c=c(j) % koeficienty cj (viz. prednaska)
        suma = 0;
        for k = 1:N  
            suma = suma + func( cos(pi/N*(k-0.5)) )  *  cos( pi/N*(k-0.5)*(j) );
        end
        c = 2*suma/N;
    end

    % rekurentni definice n Cebysevovych polynomu v bode xx
    
    function T=T(xx)     
        T0=1; %Matlab indexuje od dáme mimo pole
        T = zeros(N-1,1);
        T(1) = xx;
        T(2) = 2*xx*T(1) - T0;
        for ii=3:N-1
            T(ii) = 2*xx*T(ii-1) - T(ii-2);
        end
    end

cj = zeros(N-1,1);
c0=c(0);
for i = 1:N-1
    cj(i) = c(i);
end

krok = (b-a) / bodu;
x = a;

xarr = zeros(bodu,1);
yarr = zeros(bodu,1);

for i = 1:bodu
    Tj=T(trans(x)); % hodnoty Cebysevovych polynomu v bode x
    y = 0.5*c0*1;  % c0 prvni scitanec
    for j = 1:N-1     % cj(j) - koeficient cj, tj(j) j-ty polynom v bode x
        y = y + cj(j)*Tj(j);  
    end
    xarr(i) = x; % ulozime aktualni x
    yarr(i) = y; % a aktualni y
    x = x+krok;  % posuneme se na dalsi x
end


x1= a:krok:b-krok;
y1= zadanafce(x1);
plot(x1,y1,'b-',xarr,yarr,'r-');
title('Aproximace Cebysevovymi polynomy');
legend('Původni','Aproximovaná')
figure;
plot(x1,yarr'-y1);
title('Chyba aproximace');

end
