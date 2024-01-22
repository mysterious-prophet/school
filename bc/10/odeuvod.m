function odeuvod

T=5;
uH=1; uM=1; uE=1; % počáteční podmínky
tA=0:0.01:T;


%Bakterie:
f=inline('(1+cos(x)).*y;','x','y'); 
h=0.1;
exact=exp(tA + sin(tA));


%Stiff
%f=inline('-15.*y','x', 'y'); % definice funkce f, plati ze u'=f(t,u)
%h=0.14; % pouzijeme krok h
%exact=exp(-15.*tA);
%hranice mezi 0.13 a 0.14


plot(tA,exact,'c'); % zobrazime aktualni polohu
pocetKroku=50; % celkovy pocet kroku

for i=0:pocetKroku
   
   t=i/pocetKroku*T; % spocteme cas odpovidajici kroku
   
   hold on;% nastavime grafy aby se nemazaly, ale aby se jen pridavaly objekty do existujicich grafu

   %EULER
   plot(t,uE,'r-*'); % zobrazime aktualni polohu
   uE=uE+h*f(t,uE); % spocteme novou hodnotu promenne u

   %MIDPOINT
   plot(t,uM,'g-*'); % zobrazime aktualni polohu
   uM=uM+h*f(t+h/2,uM+h/2*f(t,uM));

   %HEUN
   plot(t,uH,'b-*'); % zobrazime aktualni polohu
   uH=uH+h/2*(f(t,uH)+f(t+h,uH+h*f(t,uH)));

   hold off;
end
legend('A','E','M','H')
%axis([0 1 -3 3]);

end

