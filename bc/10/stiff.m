function stiff

function r=y(x)
    r=exp(-100*x)+exp(-x);
end

function r=f(x,y,z)
    r(1)=z;
    r(2)=-100*y-101*z;
end

a=0;
b=0.7;
%b=0.8;
%b=0.9;

h=(b-a)/40

xn=a:h:b;
yn2=ones(1,length(xn));
zn2=zeros(1,length(xn));
yn4=ones(1,length(xn));
zn4=zeros(1,length(xn));

figure;
yn=y(xn);
m=max(max(abs(yn)));
plot(xn,yn);

yn2(1)=2;
zn2(1)=-101;
yn4(1)=2;
zn4(1)=-101;

hold on

plot(xn(1),yn2(1),'LineStyle','none','Marker','*','Color',[0 0 0]);
plot(xn(1),yn4(1),'LineStyle','none','Marker','o','Color',[1 0 0]);
	


for i=1:length(xn)-1

	pause(0.1);

	%RK2
	k1=h*f(xn(i),yn2(i),zn2(i));
	k2=h*f(xn(i)+h,yn2(i)+k1(1),zn2(i)+k1(2));
	
	yn2(i+1)=yn2(i)+1/2*(k1(1)+k2(1));
	zn2(i+1)=zn2(i)+1/2*(k1(2)+k2(2));
	
	plot(xn(i+1),yn2(i+1),'LineStyle','none','Marker','*','Color',[0 0 0]);
	
	%RK4
	k1=h*f(xn(i),yn4(i),zn4(i));
	k2=h*f(xn(i)+1/2*h,yn4(i)+1/2*k1(1),zn4(i)+1/2*k1(2));
	k3=h*f(xn(i)+1/2*h,yn4(i)+1/2*k2(1),zn4(i)+1/2*k2(2));
	k4=h*f(xn(i)+h,yn4(i)+k3(1),zn4(i)+k3(2));
	
	yn4(i+1)=yn4(i)+1/6*(k1(1)+2*k2(1)+2*k3(1)+k4(1));
	zn4(i+1)=zn4(i)+1/6*(k1(2)+2*k2(2)+2*k3(2)+k4(2));
	
	plot(xn(i+1),yn4(i+1),'LineStyle','none','Marker','o','Color',[1 0 0]);
end

legend('funkce','RK2 funkce','RK4 funkce');

hold off

end
