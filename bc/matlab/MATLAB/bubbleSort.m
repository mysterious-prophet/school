function x = bubbleSort(x, type)
if nargin == 1
    type = 'ascend';
end
n = length(x);
if n == 1
    return
else
    for j = 1:n-2
        flag = 0;
        for i=1:n-j
            if x(i) > x(i+i)
                pom = x(i);
                x(i) = x(i+1);
                x(i+1) = pom;
                flag = 1;
            end
        end
        if flag == 0
            break
        end
    end
end