%rosenbrock

% a = 1;
% % b = 100;
% f = @(x, y) (a-x).^2 + b*(y - x.^2).^2;
f =@ (x) (x(1) - 1).^2+100*(x(2)-x(1).^2).^2;
x = -2:0.1:2;
y = -1:0.1:3;
[X, Y] = meshgrid(x, y);
Z = [X(:) Y(:)];
F = 0*X(:);

for i=1:length(X(:))
    F(i) = f(Z(i,:));
end

F1 = reshape(F, size(X));
h0 = figure;
 v = VideoWriter('Anim3D.avi'); open(v);
surf(X, Y, F1, -F1, 'EdgeColor', 'none')
g = @(x) [2*(x(1) - 1) - 400*x(1)*(x(2)-x(1)^2); 200*(x(2)-x(1)^2)];
H = @(x) [(2-400*(x(2)-x(1)^2) + 800*x(1)^2) -400*x(1); -400*x(1) 200];
x0 = [2 -1]';
f0 = f(x0);
hold on
h1 = plot3(x0(1), x0(2), f0, '*');
alpha = 1/4;
delta = 1e-8;
while 1
    g0 = g(x0);
    H0 = H(x0);
    x1 = x0-alpha*inv(H0)*g0;
    f1 =f(x1);
    set(h1, 'XData', x1(1), 'YData', x1(2), 'ZData', f1);
    drawnow, pause(1);
    frame = getframe(gcf);
    writeVideo(v, frame);
    if norm(x1-x0) < delta
        break
    end
    x0 = x1;
end
