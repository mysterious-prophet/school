% skript simulujici rovnici brzdne drahy meteoritu v atmosfere
% diferencialni rovnice dv(t)/dt = -v(t), v(0) = 1
% spocitame vyvoj rychlosti v case pomoci konecne diference derivace
% dv(t)/dt => v(t+dt)-v(t-dt)/2dt, 
% kde dt je konecne cislo
clear all;

T = 10;
dt = 0.3;
N = T/dt;

% pocatecni podminky
t(1) = 0;
v(1) = 1;

% druhy casovy krok
t(2) = t(1) + dt;

% presne reseni v prvnich dvou bodech
v_exact(1) = exp(-t(1));
v_exact(2) = exp(-t(2));

% schema je tribodove, takze poterbujeme jeste jednu hodnotu v(2)
v(2) = v_exact(2);

% diferencni schema v(t+dt)-v(t-dt)/2dt = -v(t)
for i=3:N
   t(i) = t(i-1) + dt;
   v(i) = v(i-2) -2*dt*v(i-1);
   v_exact(i) = exp(-t(i));
end    

plot(t, v, 'bx', t, v_exact, 'r-');
legend('numerics','exact');
