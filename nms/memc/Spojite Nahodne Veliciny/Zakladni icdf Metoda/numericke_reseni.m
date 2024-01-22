%Ukazka numerickeho reseni rovnic

close all
clear variables
clc


%% Reseni rovnice f(x) = 0 pro x

% funcke f(x)
f = @(x) x - 2;
% vime ze reseni f(x) = 0 je 2, ale delame, ze nevime
% pouzijeme numericky resic
% predame mu funkci a uvodni odhad
% uvodni odhad
x0 = 0;
% vyreseni rovnice
x_num = fzero(f, x0);
% vypis numerickeho reseni
disp('Reseni f(x)=0:')
disp(x_num)


%% Reseni rovnice f(x) = c pro x

% rovnici prevedu na tvar f(x) - c = 0
% jde zapsat jako g(x) = 0;

% hodnota c muze by nahodna
c = rand() * 3;
% definuji funci g
g = @(x) f(x) - c;
% resim
x2_num = fzero(g, x0);
% vypis reseni
disp('Reseni f(x)=c:')
% num2str: z cisla udela znaky, pote je spojime s polem znaku pomoci []
disp(['c = ', num2str(c)])
disp(['x = ', num2str(x2_num)])
