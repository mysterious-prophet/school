function derivace2(x,h)

    function f = f(x) 
        f = sin(x); % zadana funkce
    end

    function df = df(x)
        df = cos(x); % zname analyticke vyjadreni derivace
    end


    function df = df_n1(x,h) % odhad derivace metodou prvniho radu
        df = ( f(x+h)-f(x) ) / h; 
    end

    function df = df_n2(x,h) % odhad derivace metodou druheho radu
        df = ( f(x+h/2)-f(x-h/2) ) / h;
    end

% ukladani mezivysledku pro zobrazeni grafu
deriv = [];
odhad_1 = [];
odhad_2 = [];
h_arr = [];     

while h > 1e-15         % zkousime ruzne velky krok
    deriv = [deriv df(x)];          % presna
    odhad_1 = [odhad_1 df_n1(x,h)]; % 1. rad
    odhad_2 = [odhad_2 df_n2(x,h)]; % 2. rad
    h_arr = [h_arr h];
    
    h = h/1.1; % zmensime krok
end

p1 = loglog(h_arr,abs( (odhad_1-deriv)./deriv ),'r-');
hold on;
p2 = loglog(h_arr,abs( (odhad_2-deriv)./deriv ),'g-');
legend([p1 p2], {'prvni rad' 'druhy rad'});
hold off;

end
