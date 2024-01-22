% load dataproukol1.txt
% [num, txt, raw] = xlsread("DataproUkol1.xlsx");

A = xlsread("DataproUkol1.xlsx", 'B2:Q1000' );
[~, x] = xlsread('DataproUkol1.xlsx', 'B1:Q1000');

prumer = mean(A); 
% std(A);
% min(A);
% max(A)
% mod(A)
% median(A);
% skewness(A);
% kurtosis(A);

fid = fopen('data.txt', 'w');
fprintf(fid, '%10s %10s %10s %10s %10s %10s \n', '', x{1:5});
fprintf(fid, '%10s %10.2f %10.2f %10.2f %10.2f %10.2f \n', 'prumer', prumer(1:5));
% fprintf(fileIS< '%6.2f %12.7f \n', A);
% fclose(fileID);
