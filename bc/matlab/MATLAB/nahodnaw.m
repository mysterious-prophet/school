% function x = tnahodnavel(n, nu)
n = 1e3;
nu = 3.7;
[w, u] = generw(n);

while 1
    z = w(w>1);
    p = w;
    m = length(z);
    if m == 0
        break
    else
        [w1, u1] = generw(m);
        w(p>1) = w1;
        u(p>1) = u1;
    end
end
c = u./sqrt(w);
r = sqrt(nu*(w.^(-2/nu)-1));
x = r.*c;
hist(x, 50);
