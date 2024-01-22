clear; clc; close all
load iris_dataset
X = irisInputs'; T = irisTargets';
a = 0.6; b = 0.2;
[X1, T1, X2, T2, X3, T3] = dividedata2(X, T, a, b);
hmin = 2; hmax = 32;
TPbest = 0;
for i = hmin:hmax
    [W, V] = MLPN4klasif(X1, T1, i);
    o2 = o2generator(X2, W, V);
    o2 = round(o2);
    TP = classevaluator(T2, o2);
    if sum(TP) > TPbest
        TPbest = sum(TP);
        hbest = i;
    end
end

Xs = [X1; X2]; Ts = [T1; T2];
[Ws, Vs] = MLPN4klasif(Xs, Ts, hbest);
o3 = o2generator(X3, Ws, Vs);
o3 = round(o3);
C = confusionmatrix(T3, o3);
[TP, FP, TN, FN] = classevaluator(T3, o3);
%graf co nefunguje
b = bar([TP', FN'], 0.9);
b(1).FaceColor = 'm';
b(2).FaceColor = 'b';
h1 = gca;
h1.XTickLabel = {'sentosa', 'virginica', 'versicolor'};
title('Vizualizace vysledku klasifikace');
legend('TP', 'FN', 'Location', 'SouthOutSide', 'Orientation', 'Horizontal');