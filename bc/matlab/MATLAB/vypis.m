clear; clc;
A = xlsread('data.xlsx', 'B3:Q1000');
[~, vname] = xlsread('data.xlsx', 'B2:Q2');
out = descriptivestats(A);
names = fieldnames(out);
fprintf( 'Tabulka 1: Deskriptivni statistiky analyzovanych dat \n');
fprintf( '===================================================== \n');
fprintf( '%10s %10s %10s %10s %10s %10s \n','', vname{1:5})
for i = 1:length(names)
    fprintf( '%10s %10.2f %10.2f %10.2f %10.2f %10.2f \n', names{i},...
    out.(names{i})(1:5)) 
end


fid = fopen('tabulka.txt', 'wt');
fprintf(fid, 'Tabulka 1: Deskriptivni statistiky analyzovanych dat \n');
fprintf(fid, '===================================================== \n');
fprintf(fid, '%10s %10s %10s %10s %10s %10s \n','', vname{1:5});
for i = 1:length(names)
    fprintf(fid, '%10s %10.2f %10.2f %10.2f %10.2f %10.2f \n', names{i},...
    out.(names{i})(1:5)); 
end

fclose(fid);

save impdata.mat A
load('impdata.mat')