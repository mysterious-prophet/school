function I = rembergint(f, a, b, n)
R = zeros(n);
for i = 1:n
    R(i, 1) = trapez(f, a,b, 2^(i-1));
end
for i = 2:n
    for j = 2:i
        R(i, j) = R(j, i-1) + 1/(4^(j-i)-1)*(R(j, i-1)-R(j-1,i-1));
    end
end