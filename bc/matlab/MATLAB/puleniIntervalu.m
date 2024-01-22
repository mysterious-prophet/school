%animace puleni intervalu

clear; clc; close all
C = 5; JH = 100; P = 102;

f = @(r) C./(1+r) + C./(1+r).^2 + C./(1+r).^3 +C./(1+r).^4 +...
    (C+JH)./(1+r).^5 - P;
x = 0:0.001:0.25; fx = f(x);
h0 = figure('Color', 'w');
plot(x, fx);
ylabel('\it P', 'Fontsize', 13);
xlabel('\it r', 'Fontsize', 13);

title('Ilustrace metody puleni intervalu');

xlim([0,0.25]); ylim([-60, 25]); grid on;
a = x(1); fa = fx(1); xp1 = a; yp1 =fa;
b = x(end); fb = fx(end); xp2 = b; yp2 = fb;
hold on;

h1 = plot(xp1, yp1, 'og', 'MarkerSize', 3, 'MarkerFaceColor', 'g'); pause(1);
h2 = plot(xp2, yp2, 'or', 'MarkerSize', 3, 'MarkerFaceColor', 'm'); pause(1);
stop = 0; delta = 1e-10; k = 0; kmax = 100;

while ~stop
    c = (a+b)/2; fc = f(c);
    zoom on
    if fa*fc < 0
        b = c; fb = fc;
        xp2 = [xp2 b]; 
        yp2 = [yp2 fb];
        set(h2, 'XData', xp2, 'YData', yp2);
        drawnow, pause(1);
    else
        a = c; fa = fc;
        xp1 = [xp1 a]; 
        yp1 = [yp1 fa];
        set(h1, 'XData', xp1, 'YData', yp1);
        drawnow, pause(1);
    end
    if fa - fb < delta || b-a < delta || k >=kmax
        stop = 1;
    end
    k = k+1;
end
zoom out
        