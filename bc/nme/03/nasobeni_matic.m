function nasobeni_matic
    A = load('matice1.txt');
    B = load('matice2.txt');
    [r1,s1] = size(A);
    [r2,s2] = size(B);
    
    C=zeros(max(size(A)));
    if r1~=s2
        error('nespravna velikost matic');
    end
    
    for i = 1:1:r1
       for j = 1:1:s2
           for k = 1:1:s1
               C(i,j) = C(i,j) + A(i,k)*B(k,j);
           end
       end
    end   
    disp(C);    
end