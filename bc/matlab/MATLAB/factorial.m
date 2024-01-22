function [f] = factorial(n)
if (n > 0 && round(n) == n)
    f = 1;
    %n*factorial(n-1); % rekurze
    while n>1
        f = f*n;
        n = n-1;
    end
    
else 
    disp("No solution");
end