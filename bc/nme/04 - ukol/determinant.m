function[detA] = determinant(A)
    A = load('matice.txt'); %nactememe zadanou matici
    [L,U] = ludekomp(A); %ziskame L a U pomoci skriptu ze cviceni
    n = size(A,1);
    detU = 1;
    detL = 1;
    for i = 1:n %det trojuhelnikove matice je produkt prvku na diagonale
        detU = detU * U(i,i);
        detL = detL * L(i,i);
    end
    detA = detU * detL; %dle LAL det(A) = det(U) * det(L)
    %detA = det(A); %kontrola det(A) = -48
end