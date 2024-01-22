%generovani nahodnych cisel
x = rand(1e3, 1);
hist(x)
x1 = randn(1e5, 1);
figure;
hist(x1, 50);