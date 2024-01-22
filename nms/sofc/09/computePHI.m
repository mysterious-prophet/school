function PHI = computePHI(X, C, k)
    d = @(x, c) sqrt(sum((x - c).^2, 2));
    m = size(X, 1);
    PHI = zeros(m, k);
    for i = 1:k
        Z = repmat(C(i, :), m, 1);
        PHI(:, i) = d(X, Z);
    end
    PHI = [ones(m, 1) PHI];
end