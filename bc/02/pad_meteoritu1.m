% skript simulujici rovnici brzdne drahy meteoritu v atmosfere
% diferencialni rovnice dv(t)/dt = -v(t), v(0) = 1
% spocitame vyvoj rychlosti v case pomoci konecne diference derivace
% dv(t)/dt => v(t+dt)-v(t)/dt, 
% kde dt je konecne cislo
clear all;

T = 10;
dt = 0.3;
N = T/dt;

% pocatecni podminky
t(1) = 0;
v(1) = 1;

% presne reseni
v_exact(1) = exp(-t(1));

% diferencni schema v(t+dt)-v(t)/dt = -v(t)
for i=2:N
   t(i) = t(i-1) + dt;
   v(i) = v(i-1)*(1-dt);
   v_exact(i) = exp(-t(i));
end    

plot(t, v, 'bx', t, v_exact, 'r-');
legend('numerics','exact');
