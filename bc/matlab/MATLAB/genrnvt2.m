function x = genrnvt2(n, nu)
x = zeros(n,1);
for i = 1:n
    [w, u] = generw(n);
    while w>1
        [w, u] = generw(1);
    end
    c = u/sqrt(w);
    r = sqrt(nu*(w^(-2/nu)-1));
    x(i) = r*c;
end