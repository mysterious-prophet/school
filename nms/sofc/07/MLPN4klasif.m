function [W, V, o2] = MLPN4klasif(X, T, h)
    [m,n] = size(X); X = [ones(m,1) X];
    O = size(T,2); beta = 1;
    W = beta*(1 - 2*rand(n+1,h));
    V = beta*(1 - 2*rand(h+1,O));
    dW = zeros(size(W)); dV = zeros(size(V));
    F = @(z) 1./(1 + exp(-z));
    delta = 1e-4; alpha = 0.05; rho = 0.05; sse0 = inf;
    k = 0; kmax = 1e4;
    while 1 
        o1 = F(X*W);
        in2 = [ones(m,1) o1];
        o2 = F(in2*V);
        err = T - o2;
        sse = err(:)'*err(:);
        Delta1 = o2.*(1 - o2).*err;
        Delta2 = (o1.*(1 - o1)).*(Delta1*V(2:end, :)');
        W = W + dW;
        dV = rho*dV + alpha*in2'*Delta1;
        V = V + dV;
        if (abs(sse - sse0) < delta || k > kmax)
            break
        else
            k = k+1;
            sse0 = sse;
        end
    end
end