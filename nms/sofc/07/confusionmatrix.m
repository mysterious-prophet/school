function C = confusionmatrix(T, o)
    [m, n] = size(T);
    C = zeros(n);
    for i = 1:n
        for j = 1:n
            pom = zeros(m, 1);
            pom(T(:, i) == 1 & o(:, j) == 1) = 1;
            C(i, j) = sum(pom);
        end
    end
end