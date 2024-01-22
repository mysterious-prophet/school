%hodiny
clear; clc; close all



%vnejsi kruh
R = 10;
theta = 0:pi/20:2*pi;
x = R*cos(theta);
y = R*sin(theta);
plot(x, y, 'Color', 'k', 'LineWidth', 3);

hold on 

%vnitrni kruh
r = 8;
phi = 0:pi/30:2*pi;
xv = r*cos(phi);
yv = r*sin(phi);
plot(xv, yv, 'ok', 'MarkerFaceColor', 'k', 'MarkerSize', 3);
for i = 0:5:60
      phi = 0:pi/6:2*pi;
      xv = r*cos(phi);
      yv = r*sin(phi);  
      plot(xv, yv, 'ok', 'MarkerFaceColor', 'k', 'MarkerSize', 5);    
end

%kruh vterinove
rVt = 2.25;
yKVts = -5;
phiVt = 0:pi/6:2*pi;
xKVt = rVt*cos(phiVt);
yKVt = rVt*sin(phiVt)+yKVts;
plot(xKVt, yKVt, 'ok', 'MarkerFaceColor', 'k', 'MarkerSize', 2.5);


%stred
xs = 0; ys = 0;
plot(xs, ys, 'ok', 'MarkerFaceColor', 'k');

%stred vterinove
xSVt = 0; ySVt = -5;
plot(xSVt, ySVt, 'or', 'MarkerFaceColor' , 'r', 'MarkerSize', 3);

%cisla 3, 6, atd.
x12 = -0.5; y12 = 9;
txt12 = '12';
text(x12, y12, txt12, 'FontSize', 16);

x6 =0.; y6 = -9;
txt6 = '6';
text(x6, y6, txt6, 'FontSize', 16);

x3 = 9; y3 = 0;
txt3 = '3';
text(x3,y3, txt3, 'FontSize', 16);

x9 = -9.5; y9 = 0;
txt9 = '9';
text(x9, y9, txt9, 'FontSize', 16);

%text vyrobce
xVyr = -1.3; yVyr = 4;
txtVyr = "Omega";
text(xVyr, yVyr, txtVyr,'FontName', 'Courier',  'FontSize', 12, 'FontAngle', 'italic');

axis off equal;

%rucicky a datum
c = clock; %vrati datum a cas
iVt = round(c(6));
iMi = c(5);
iHo = c(4);
day = c(3);
month = c(2);
year = c(1);

%den v mesici
xday = 4; yday = 0;
txtDay = int2str(day);
text(xday, yday, txtDay, 'FontSize', 13);
rectangle('position', [4 -0.7 1.2 1.2], 'edgecolor' , 'r');

%debugg
%  iVt = 58; 
%  iMi = 59;
%  iHo = 23;
while 1
    %vterinova
    psiVt = pi/2 +(-iVt*pi/30);
    xVtP = -cos(psiVt);
    yVtP = -sin(psiVt)+yKVts;
    xVtK = rVt*cos(psiVt);
    yVtK = rVt*sin(psiVt)+yKVts;
    vt = line([xVtP xVtK], [yVtP yVtK], 'Color', 'r');
    
    %minutova
    psiMi = pi/2 + (-iMi*pi/30);  
    xMiP = -1.5*cos(psiMi);
    yMiP = -1.5*sin(psiMi);
    xMiK = 7*cos(psiMi);
    yMiK = 7*sin(psiMi);
    mi = line([xMiP xMiK], [yMiP yMiK], 'Color', 'k', 'LineWidth', 2);
    posMi = rem(iVt, 60);
    if (posMi == 0)
       iVt = 0; 
       iMi = iMi+1; 
    end
    
    
    %hodinova
    psiHo = pi/2 + (-iHo*pi/6);
    xHoP = -1.5*cos(psiHo);
    yHoP = -1.5*sin(psiHo);
    xHoK = 6*cos(psiHo);
    yHoK = 6*sin(psiHo);
    ho = line([xHoP xHoK], [yHoP yHoK], 'Color', 'k', 'Linewidth', 2.5);
    posHo = rem(iMi, 60);
    if(posHo == 0 && posMi == 0)
        iMi = 0;
        iHo = iHo + 1;
    end
    if(iHo == 24)
        iHo = 0;
        day = day+1;
        txtDay = int2str(day);
        text(xday, yday, txtDay, 'FontSize', 16);
    end
    
    
    pause(1);
    
    set(vt, 'Visible', 'off');
    set(mi, 'visible', 'off');
    set(ho, 'visible', 'off');
    iVt = iVt+1;
    
end




