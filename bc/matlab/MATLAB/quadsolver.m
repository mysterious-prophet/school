function [x1,x2] = quadsolver(a,b,c)
    D = (b^2)-(4*a*c);
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
end
    