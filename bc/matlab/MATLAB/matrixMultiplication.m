%matrix multiplication

clear;
close all;
clc;

X = [1 2 ; 3 4];
Y = [3 4; 1 2];

C = X*Y;
D = X.*Y;


%display(C);
%display(D);


[m,n] = size(X);
[p,q] = size(Y);

Z = zeros(m,q);

for i = 1:m
    for j = 1:q
        Z(i,j) = X(i,:) * Y(:,j); % : all elements
    end
    
end

display(Z);