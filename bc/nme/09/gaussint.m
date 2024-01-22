function gaussint

% na kazdem radku je prislusna vaha a bod
vahy = [1	0.4179591836734694	0.0000000000000000
2	0.3818300505051189	0.4058451513773972
3	0.3818300505051189	-0.4058451513773972
4	0.2797053914892766	-0.7415311855993945
5	0.2797053914892766	0.7415311855993945
6	0.1294849661688697	-0.9491079123427585
7	0.1294849661688697	0.9491079123427585];

f = inline('sin(x)*exp(cos(x))','x');

% integracni meze
a=0;
b=pi;

integral = 0;

m = size(vahy,1);   % pocet bodu

for i=1:m
    % vahy(i,1) da i-ty bod, vahy(i,2) da i-tou vahu
    % body jsou preskalovane z (-1,1) na (a,b)
    integral = integral+vahy(i,2)*f( ( (b-a)*vahy(i,3) + (a+b) )/2 );
end

integral = integral * (b-a)/2

hold on
  plot(1,integral,'mx')
hold off

end
