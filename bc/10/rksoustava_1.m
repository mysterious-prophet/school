function rksoustava_1

%demonstrace metody Runge-Kuta ctvrteho radu pro reseni soustavy dvou rovnic druheho radu

%problém dvou těles

T=20; % budeme integrovat 20 sekund
h=0.01; % pouzijeme krok h
%u=[x  dx   y  dy ]
u =[1  0 0 1 ];  % počáteční podmíky
%u =[1  -0.3 0 0.3 ];

axis([-1 1 -1 1]);
f=inline('[w(2),-w(1)*(w(1)^2 + w(3)^2)^(-3/2),w(4), -w(3)*(w(1)^2 + w(3)^2)^(-3/2)]','w'); % definice funkce f, plati ze u'=f(t,u)

pocetKroku=T/h; % celkovy pocet kroku

%prvni krok Eulerova metoda
u_t_nm1 = u;
u(1)=u_t_nm1(1) + h*u_t_nm1(2);
u(2)=u_t_nm1(2) - (h*u_t_nm1(1))/(((u_t_nm1(1))^2+(u_t_nm1(3))^2)^(3/2));
u(3)=u_t_nm1(3) + h*u_t_nm1(4);
u(4)=u_t_nm1(4)- (h*u_t_nm1(3))/(((u_t_nm1(1))^2+(u_t_nm1(3))^2)^(3/2));

%potom leap-frog
for i=1:pocetKroku    
    pause(0.01);
    hold on;
    plot(u(1),u(3),'r.'); % zobrazime aktualni polohu
    hold off;
    
    %ux(tn+1) = ux(tn-1)+-2h*uy(tn);
    u_t_n = u;
    u(1) = u_t_nm1(1) + 2*h*u_t_n(2);
    u(2) = u_t_nm1(2) - (2*h*u_t_n(1))/(((u_t_n(1))^2 + (u_t_n(3))^2)^(3/2));
    u(3) = u_t_nm1(3) + 2*h*u_t_n(4);
    u(4) = u_t_nm1(4) - (2*h*u_t_n(3))/(((u_t_n(1))^2 + (u_t_n(3))^2)^(3/2));
     
    u_t_nm1 = u_t_n;
end 
end
