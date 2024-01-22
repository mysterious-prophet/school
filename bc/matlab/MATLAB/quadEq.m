%quadratic equation solver ax^2+bx+c

clear;
close all;
clc;

disp('Solves ax^2+bx+c');
a = input('a = ');
b = input('b = ');
c = input('c = ');

D = (b^2)-(4*a*c);
disp('Discriminant is: ');
display(D);

disp('Solution of given equation is: ');
    if D > 0
        x1 = (-b+sqrt(D))/(2*a);
        x2 = (-b-sqrt(D))/(2*a);
    end
    if D == 0
        x1 = -b/(2*a);
    end
    if D<0
        disp('No solution for real numbers');
    end
    
    
        