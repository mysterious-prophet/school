function[Q,R] = qrRozkladFunc(A)
% A = randi([-5,5], [2,2]);
A = [1 2; 3 4];
[m,n] = size(A);
Q = eye(m);
R = A;

for j=1:min(m,n)
    x = R(j:m, j);
    if x(1) ~= norm(x)
        x(1) = x(1) - norm(x);
        Hx = eye(m-j+1)-2*((x*x')/(x'*x));
        H = [eye(j-1) zeros(j-1, m-j+1); zeros(m-j+1, j-1) Hx];
        R = H*R;
        Q = H*Q;
    end
end
Q = Q';