A = [9 5 7 1 3; 8 8 3 6 6; 7 7 3 3 5; 9 8 4 6 7; 6 5 8 7 3];
n = size(A, 1);
mi1 = min(A, [], 2);
A = A - repmat(mi1, 1, n);
mi2 = min(A);
A = A - repmat(mi2, n, 1);