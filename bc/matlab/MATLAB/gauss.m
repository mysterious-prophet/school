clear; close; clc
A = randi([-5,5], [7,8]);
disp(A);

n = size(A);
n = n(1);

for k = 1 : n-1     
    for i = k+1 : n
        for j = k : n
            A(i,j) = A(i,j) - (A(i,k)/A(k,k)) *  A(k,j);
            
        end
    end
end

for i = 1 : n    
  A(i, :) = A(i, :)/A(i,i);
end

disp(A);