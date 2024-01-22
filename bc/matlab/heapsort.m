
function B = heapsort(A)

%pole na sort
A = [4 10 3 5 1 8 -2];

%velikost pole k razeni
[~,n] = size(A);
%pole s vysledkem
B = zeros(1, n);

for i = 1:n
    A = buildHeap(A);
    
    %nejvetsi prvek, vrchol na konec pole s odpovedi
    B(n+1-i) = A(1);
    
    %posunuti nejvetsiho prvku, vrcholu na konec a jeho odstraneni
    temp = A(1);
    A(1) = A(n+1-i);
    A(n+1-i) = temp;    
    A(n+1-i) = [];
    
    %vytvoreni haldy ze zbyvajiciho pole
   %A = heapify(A,1);

end
end

function A = buildHeap(A)
[~,n] = size(A);

%pozice vrcholu
m = floor(n/2);

for i = m:-1:1
    A = heapify(A,i);
end
end

function A = heapify(A,i)
[~,n] = size(A);

%levy a pravy potomek
left = 2*i;
right = 2*i + 1;

%nalezeni noveho vrcholu
if left <= n
    if A(left) >= A(i)
        top = left;
    else
        top = i;
    end
else
    return
end

if right <= n
    if A(right) >= A(top)
        top = right;
    end
end

%zmena vrcholu
if top ~= i
    temp = A(top);
    A(top) = A(i);
    A(i) = temp;
    %prehazeni potomku
    A = heapify(A, top);
end
end
