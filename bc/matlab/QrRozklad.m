% QR rozklad matice
%  function[Q,R] = QrRozklad(A)

% A =  [ -1   9   2   8   7;
%   5   6  -5   7   2;
%  -9   0   1   2  -3]

A = [12 -51 4;
    6 167 -68;
    -4 24 -41];

[m,n] = size(A);

% gram schmidt
%     U = zeros(m, m);
%     U(:, 1) = A(:, 1);
% 
%     E = U;
% 
%     for i = 2:m
%         U(:,i) = A(:, i);
%         for j = i:m
%             U(:, j) = U(:, j)-(dot(U(:,j-1),A(:,j)))/(dot(U(:,j-1),U(:,j-1))).*U(:,j-1);
%         end
%     end
% 
%     for i = 1:m
%         E(:, i) = U(:, i)/sqrt(dot(U(:,i),U(:,i)));
%     end
% 
%     Q = E;
%     R = transpose(Q)*A;

%householder

R = A;
I = eye(m);
B = zeros(m);
U = zeros(m,m,100);
 for k = 1:n
    x = R(k:m, k);

    alpha = norm(x);
    e = zeros(length(x),1);
    e(1) = 1;

    u = x -alpha*e;
    if norm(u) ~=0
        v = u/norm(u);

        B = I(k:m,k:m) - 2*v*transpose(v);
        I(k:m, k:m) = B;
        U(:,:,k) = I;

        P =  U(:,:,k);
        for l=k-1:-1:1
            if k>0
                P = P*U(:,:,l);
            end
        end
        R = P*A;
        I= eye(3);
    end
 end
Q = P';

% givens
% Q = eye(m);
% R = A;
% cos = 0;
% sin = 0;
% rot = 0;
% 
% for j = 1:n
%     for i = m:-1:(j+1)
%         G = eye(m);
%         
%         xi = R(i-1,j);
%         xj = R(i,j);
%         
%         if xj == 0
%             cos = 1;
%             sin = 0;
%         else
%             if abs(xj) > abs(xi)
%                 rot = xi/xj;
%                 sin = 1/sqrt(1+rot^2);
%                 cos = sin * rot;
%             else
%                 rot = xj/xi;
%                 cos = 1/sqrt(1+rot^2);
%                 sin = cos*rot;
%             end
%         end
%         G([i-1,i],[i-1,i]) = [cos -sin; sin cos];
%         R = G'*R;
%         Q = Q*G;
%     end
% end

% zbaveni se malych cisel 1e-10 atd.
for i = 1:m
    for j = 1:n
        if abs(R(i,j))<1e-6
            R(i,j)=0;
        end
    end
end