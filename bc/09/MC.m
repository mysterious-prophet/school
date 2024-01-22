function MC

% integrovana funkce
f = inline('abs(sin(pi^2.*((x-0.5).^2+(y-0.5).^2)))','x','y');
%f = inline('x+y','x','y');

kroku=10000;


vysl=zeros(kroku,1); % vysledky

tic
z=0;
for i=1:kroku
  r=rand(1,2);  % dve nahodna cisla v (0,1)
  value= f(r(1),r(2));  % vypocteme funkci ve dvou nahodnych bodech
  z=z+value;    % pricteme ke kumulovane hodnote
  vysl(i)=z/i;  % prumer (kumul. hodnota delena poctem kroku)
end
integral=z/kroku
toc


vysledek = 0.6551; % abs(sin)
%vysledek = 1;   % x+y

plot(1:kroku,vysl,[1 kroku],[vysledek vysledek])

figure
dat=abs(vysl-vysledek);
chyb=(((1:kroku)).^(-1/2));
x=log10(1:kroku);
plot(x,log10(dat),x,log10(chyb));

figure
x=1:kroku;
plot(x,dat,x,chyb);

