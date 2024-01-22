function vypocetpi
figure;axes;
box on
rectangle('Position',[0,0,1,1],'Curvature',[1,1]);
hold on
bodu=0;
vkruhu=0;
npi=0;
steps = 30;

plotNum=zeros(steps,1);
plotPi=zeros(steps,1);

for i=1:steps
str=sprintf('Pocet bodu %u Vypoctene pi je %g',bodu,npi);
title(str);
waitforbuttonpress;
for j=1:500
    bodu=bodu+1;
    x=rand(1,2);
    if ((x(1)-0.5)^2 + (x(2)-0.5)^2 <0.25)
        vkruhu=vkruhu+1;
        plot(x(1),x(2),'ro');
    else
        plot(x(1),x(2),'bo');
    end
end
npi=4*vkruhu/bodu;
plotNum(i)=bodu;
plotPi(i)=npi;

end
plotPi(end)
hold off
end
