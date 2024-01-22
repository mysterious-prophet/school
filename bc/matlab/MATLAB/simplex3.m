clear; close all; clc
% A = [-1 3 1 0 0;
%     2 3 0 1 0;
%     2 -1 0 0 1];
% b = [9 18 10]';
% CT = [-4 -2 0 0 0];
% % % B = [3 4 5];%Pocatecni permutace
A = [1 1 1 0 0 0 0;
    1 -1 0 1 0 0 0;
    -1 1 0 0 1 0 0;
    1 0 0 0 0 1 0;
    0 1 0 0 0 0 1];
b = [20 10 10 14 14]';
CT = [-1 -1/5 0 0 0 0 0];
B = [3 4 5 6 7];
% A = [1 -1 1 0; %%funguji
%     -1 1 0 1];
% b = [10 10]';
% CT = [-1 -1 0 0];
% B = [3 4];
% A = [3 3 3 0 0 2 3 1 2 1 1 0 0 0 0;
%     0 1 2 2 3 0 0 0 3 2 0 1 0 0 0;
%     2 1 2 3 1 2 3 2 2 3 0 0 1 0 0;
%     2 2 0 0 3 2 0 0 0 0 0 0 0 1 0;
%     1 2 1 2 0 1 0 3 2 3 0 0 0 0 1];
% b = [100 200 300 400 500]';
% CT = [-1 -2 -3 -4 -5 -6 -7 -8 -9 -10 0 0 0 0 0];
% B = [11 12 13 14 15];

h = [0];
[m,n] = size(A);%zjisti rozmer zadane matice

disp('   Zadani:');%Zobrazi nevyresenou ulohu
Zadani = [A, b];
Zadani(m + 1,:) = [CT, h];
disp(Zadani);
krok = 0;
PODMINKA = 1;

while PODMINKA ~= 0 %cyklus bude probihat pokud v vektoru C z pruhem jsou zaporna cisla
    AB = A(: ,B); %vezme sloupce z matice A. Sloupce urcuje vektor B
    CTB = CT(:, B); %vezme prvky z vektoru CT. Prvky urcuje vektor B
    AzP = inv(AB)*A;%"inv" znamena A^-1
    bzP = inv(AB)*b;
    CzP = CT - CTB*inv(AB)*A;
    hzP = -CTB*inv(AB)*b;
    PODMINKA = sum(CzP<0); %kontrola je-li splnena podminka pro dalki cyklus
 krok = krok + 1;
    disp('   Krok:');%Zobrazi vyledek
    disp(krok);
    %PODMINKA = PODMINKA + 1;
    for i = 1 : n %zjisti index S (misto kde je zaporne cislo (jde od zacatku))
%         if abs(CzP(i)) > 0 && abs(CzP(i)) < 0.00000000010000000001
%             CzP(i) = 0;
%         end
            if CzP(i) < 0
            s = i;
            break;
        end
    end

    Vr = [1,m];%Tento vektor neni soucast algoritmu. Potrebuji jen pro sebe(pro snadnejsi vypocet)
    for i = 1: m %Spocita vektor Vr(1. slozka je A(s, 1) z pruhem / b(1) a td.)
        if AzP(i, s) == 0
           Vr(i) = realmax; 
        else
        Vr(i) = bzP(i)/AzP(i, s);
        end
    end
    
    if max(Vr) <= 0 %pokud pri vyberu pivota nebudou zadna > 0 cisla - program skonci ze spravou pro uzivatele
        error('Zadani ma nekonecne mnoho reseni');
    end
    
    for i = 1 : m %Pokud ve vektoru Vr jsou zaporna cisla, udela z nich realmax
        if Vr(i) <= 0 
            Vr(i) = realmax;
        end
    end
    
    [VrMIN,r] = min(Vr); %Najde minimum a jeho pozice ve vektoru Vr
    B(r) = s; %Nastavi novou permutace 
   
Vysledek = [AzP, bzP];
Vysledek(m + 1, :) = [CzP, hzP];
disp(Vysledek);
disp('   Permutace:');%Zobrazi konecnu permutace 
disp(B);
    
end

disp('   Vysledek:');%Zobrazi vyledek
Vysledek = [AzP, bzP];
Vysledek(m + 1, :) = [CzP, hzP];
disp(Vysledek);
disp('   Permutace:');%Zobrazi konecnu permutace 
disp(B);