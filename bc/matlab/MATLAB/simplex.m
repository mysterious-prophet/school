A = [2 4 2; 2 3 4];
b = [60 50]';
c = [30 50 40];
[m,n] = size(A);
T = [A eye(m) b; -c zeros(1,n)];
disp(T);