clear; clc; close all

A = xlsread('data.xlsx', 'B3:C1060');
[~, vnames] = xlsread('data.xlsx', 'B2:C2');

yyaxis left
plot(A(:,1));

ylabel(vnames(1));

xlabel('year');
xticks(0:250:1059);
xticklabels(2008:2012);
xlim([0 size(A,1)]);

hold on
yyaxis right
plot(A(:,2),'k');

ylabel(vnames(2));
title('Vyvoj kurzu PX a ceny ropy');