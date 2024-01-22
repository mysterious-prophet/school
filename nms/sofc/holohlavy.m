n = 0:300000;
w = 0.99999999995;

% phi(x) = x
% H = w.^n;

% phi(x) = sin(x*pi/2);
% wstar = sin(w*pi/2);
% phiH = wstar.^n;
% H = asin(phiH)*2/pi;

% phi(x) = asin..
% wstar = asin(w)*2/pi;
% phiH = wstar.^n;
% H = sin(phiH*pi/2);

% nilpotence identita
% H = max(w*n-n+1,0);

% nilpotence sin
% wstar = sin(w*pi/2);
% phiH = max(wstar*n-n+1,0);
% H = asin(phiH)*2/pi;

% nilpotence asin
wstar = asin(w)*2/pi;
phiH = max(wstar*n-n+1,0);
H = sin(phiH*pi/2);
plot(n, H, 'r.');