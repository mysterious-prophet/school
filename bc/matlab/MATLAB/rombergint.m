function I = rombergint(f, a, b, tol)
R = zeros(2);
for i = 1:2
    R(i, 1) = trapez(f, a,b, 2^(i-1));
end
R(2,2) = R(2,1) + 1/3*(R(2,1)-R(1,1));
if abs(R(2,2) - R(2,1)) < tol
    I = R(2,2);
    return
else
    stop = 1;
    while stop
        i = i+1;
        Rn = zeros(i);
        Rn(1:i-1, 1:i-1) = R;
        Rn(i,1) = trapez(f, a,b, 2^(i-1));
        for j = 2:i
            Rn(i, j) = Rn(i, j-1) + 1/(4^(j-1)-1)*(Rn(i, j-1)-Rn(i-1,j-1));
            if abs(Rn(i,j)-Rn(i,j-1))<tol
                I = Rn(i,j);
                
                return
            end
        end
        R = Rn; 
    end
       
end