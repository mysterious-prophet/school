function A = selectSort(A, type, dim)
if nargin == '1'
    type = 'ascend';
end
[m,n] = size(A); 
An = zeros(m, n); 
tic
    for j= 1:n
        b = A(:,j);
        i = 1;    
        while length(b) > 1
            [xmin, imin] = min(b);
            An(i,j) = xmin;
            i = i+1;
            b(imin) = [];
        end
        An(end,j) = b;
    end
    
A = An;
toc
