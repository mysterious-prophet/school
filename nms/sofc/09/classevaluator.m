function [TP, FP, TN, FN] = classevaluator(T, Th)
    [m,n]  = size(T);
    TP = zeros(1, n); FP = TP; TN = TP; FN = TP;
    for i = 1:n
        p = zeros(m,1);
        p(T(:,i) == 1 & Th(:,i) == 1) = 1;
        TP(i) = sum(p); p = 0*p;
        p(T(:,i) == 0 & Th(:,i) == 1) = 1;
        FP(i) = sum(p); p = 0*p;
        p(T(:,i) == 0 & Th(:,i) == 0) = 1;
        TN(i) = sum(p); p = 0*p;
        p(T(:,i) == 1 & Th(:,i) == 0) = 1;
        TN(i) = sum(p);
    end
end