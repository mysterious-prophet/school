function calculator
clear; clc; close all
% vytvoreni okra
h = figure('Units', 'Normalized', 'Position', [0.05 0.5 0.4 0.4], 'Name',...
    'CasioXXL', 'NumberTitle', 'off', 'MenuBar', 'None', 'Resize', 'off');
% vytvoreni displaye kalkulatoru
disp1 = uicontrol('Units', 'Normalized', 'Style', 'Text', 'Position', ...
    [0.03 0.70 0.77 0.25], 'String', '', 'FontSize', 24, 'FontWeight', 'bold',...
    'BackgroundColor', 'white', 'Tag', 'mmonit', 'HorizontalAlignment'...
    , 'right');

% vytvoreni seznamu tlacitek
names = {'7', '8', '9', '+', '%', '.', '4', '5', '6', '-', 'sqrt', '+/-', '1', '2', '3', '*', 'x^2',...
    'Back','0', '(',')', '/', '1/x', '='};
% rozdeleni do ctyr rad
m = 4; n = length(names)/m;
names1 = {'sev', 'eig', 'nin', 'plu', 'perc', 'dec', 'fou', 'fiv', 'six' , 'sub', 'sqrt', 'sig',...
    'one', 'two', 'thr', 'mul', 'sq', 'back', 'zer', 'lbr', 'rbr', 'div', 'inv', 'equ'};

%rozdeleni tlacite do rad
wi = 0.13; he = 0.12;
mw = 0.03; mh = 0.03;
for i = 1:m
    for j = 1:n
        l1 =  mw + (j-1)*(wi + mw);
        bb = 0.65 - he - (i-1)*(he + mh);
        uicontrol('Parent', h, 'Units', 'Normalized', ...
            'Style', 'pushbutton', 'Position', [l1 bb wi he], 'String', ...
            names{(i-1)*n+j}, 'FontSize', 16, 'FontWeight', 'bold', 'Tag',...
            names1{(i-1)*n+j}, 'Callback', @bigcallback);
    end
end

% vytvoreni tlacitka CE
uicontrol('Units', 'Normalized', 'Style', 'pushbutton', 'Position', ...
    [0.83 0.70 0.13 0.25], 'String', 'CE', 'FontSize', 21, ...
    'FontWeight', 'bold', 'Tag', 'clear', 'Callback', @clear_callback);
% vytvoreni ramecku okolo displaye
hp1 = uipanel(h, 'Units', 'Normalized', 'Position', [0.025 0.69 0.78 0.265]);
uistack(hp1, 'bottom');
hp2 = uipanel(h, 'Units', 'Normalized', 'Position', [0 0 1 1]);
uistack(hp2, 'bottom');

% celkovy pocet znamenek a desetinnych carek ve vyrazu, vycet znamenek
    signcount = 0;
    dotcount = 0;
    list = ['+', '-', '*', '/'];
    
    function bigcallback(src, ~, ~) 
        switch src.Tag
%             zmen hodnotu vyrazu, zmen dle pravidel + za - a naopak
            case 'sig'
%                 zjisti string a pocet zavorek v nem
                str = get(disp1, 'String');
                [temp,lcount] = size(strfind(str, '('));
                [temp,rcount] = size(strfind(str, ')'));
%                 nelze vyhodnotit pokud nesouhlasi pocet zavorek
                if lcount ~= rcount
                   return; 
                end
%                 delka stringu
                n = length(str);
%                 pocet znamenek
                for i=2:n
                    if(ismember(str(i), list))
                       signcount = signcount+1; 
                    end
                end
                
                if not(str=="")
%                     pokud se jedna pouze o jednoduche cislo
                    if (signcount == 0)
                        if(str(1)=='-')
                            str=str(2:end);

                        elseif(not(str(1)=='-') && not(str == "0"))
                            str = insertAfter(str,0,'-');
                        end
                    end
%                     pokud se jedna o vyraz
                    if(signcount > 0) 
%                         pomocne pocty zavorek urci jestli jsme uvnitr
%                         nejake zavorky, uvnitr ktere se znaminka nemeni
                        lbrcount = lcount;
                        rbrcount = rcount;
%                         pomocna promenna ktera urcuje jesli se ma menit
%                         znamenko +- kdyz se jedna o sub vyraz obsahujici
%                         */
                        firstmult = false;
%                         unarni +-
                            for i = 1:n
                                if(str(i) == '(')
                                    lbrcount = lbrcount-1;
                                    
                                elseif (str(i) == ')')
                                    rbrcount = rbrcount -1;
                                end
%                                 je li prvni znamenko vyrazu */ meni se je
%                                 jen jedno ze znamenek
                                if ((rbrcount == lbrcount) && (str(i) == '*' || str(i) == '/'))
                                   firstmult = true;
                                   break 
%                                    pokud je prvni znamenko +- tak se
%                                    chovej normalne
                                elseif ((rbrcount == lbrcount) && (str(i) == '-' || str(i) == '+'))
                                    firstmult = false;
                                    break;
                                end
                            end
%                           zmen unarni minus na + tedy odstan minus 
                            if(str(1) == '-')                            
                                    str = str(2:end); 
%                           pokud neni unarni minus a neni to prvni
%                           nasobeni pridej tento minus
                            elseif(not(str(1)=='-'))
                                if firstmult == false
                                    str = insertAfter(str, 0, '-');
                                end
                            end
%                             pomocne promenne pomahaji urcit, zda jsme
%                             uvnitr zavorek, delku str, zda se jedna o
%                             jednoduchou zavorku (pouze cislo) a zda se
%                             jedna o nasobeni deleni
                            lbrcount = lcount;
                            rbrcount = rcount;
                            n = length(str);
                            lastpos = 1;                        
                            singlebracket = false;
                            firstmult = false;
                            erasure = false;
%                             zmena +- ve zbytku vyrazu
                            for i=lastpos:n
%                                 dochazelo k prekroceni indexu n
                                if (not(i>n))
%                                     zjisti, zda jsme uvnitr zavorky bud
%                                     slozene nebo jednoduche. ve slozene
%                                     se pravidla neuplatnuji
                                    if(erasure == true)
                                       i = i-1; 
                               
                                    end
                                    if(str(i) == '(' )
                                        lbrcount = lbrcount-1;
    %                                     firstmult = not(firstmult);
                                        singlebracket = true;
                                        for k = i+2:n
                                            if str(k) == ')'
                                                break
                                            elseif ismember(str(k), list)
                                                singlebracket = false;                                           
                                            end
                                        end
                                    elseif(str(i) == ')')
                                        rbrcount = rbrcount - 1;
    %                                     firstmult = not(firstmult);
                                        singlebracket = false;
                                    end

%                                   pravidla zmeny znamenek - po */
                                    if( (i>1 && str(i-1) == '*' && str(i) == '(' && singlebracket == false && erasure == false && firstmult == false && lcount <2) || i>1 && str(i-1) == '*' && not(str(i)=='-') && firstmult == false && lbrcount==rbrcount)
                                        str = insertAfter(str,i-1, '-');                                        
                                        n = n+1;
                                        i = i+1;
                                        firstmult = not(firstmult);
                                        erasure = false;
                                    elseif((i>1 && str(i-1) == '/' && str(i) == '(' && singlebracket == false && erasure == false && firstmult == false) || i>1 && str(i-1) == '/' && not(str(i)=='-') && lbrcount == rbrcount && firstmult == false)    
                                        str = insertAfter(str,i-1, '-');                                   
                                        n = n+1; 
                                        i = i+1;
                                        firstmult = not(firstmult);
                                    elseif(i>1 && str(i-1) == '*' && str(i) == '-' && lbrcount == rbrcount && firstmult == false)
                                         str = eraseBetween(str, i,i);
                                         n = n-1;
                                         erasure = true;  
                                         firstmult = not(firstmult);
                                    elseif(i>1 && str(i-1) == '/' && str(i) == '-' && lbrcount == rbrcount && firstmult == false)
                                        str = eraseBetween(str, i, i);
                                        n = n-1;
                                        erasure = true; 
                                        firstmult = not(firstmult);
%                                         zmena jednoduchych +-
                                    elseif(i>1 &&str(i)=='+' && lbrcount == rbrcount)
                                        str(i) = '-';   
%                                         i = i;
                                         firstmult = not(firstmult);
                                    elseif(i>1 &&str(i)=='-' && lbrcount == rbrcount)
                                        str(i) = '+';   
%                                         lastpos = i;
                                        firstmult = not(firstmult);
%                                   nemen znamenko argumentu sqrt
                                    elseif(singlebracket == true && str(i-1) == 't')
                                        singlebracket = false;
%                                   zmena znamenka v jednoduchych zavorkach
                                    elseif(singlebracket == true && not(str(i+1) == '-'))
                                        str = insertAfter(str, i, '-');
                                        n = n+1;
                                        i = i+1;
                                        singlebracket = false;
                                    elseif(singlebracket == true && str(i+1) == '-')
                                        str = eraseBetween(str, i+1, i+1);
                                        n = n-1;
                                        %erasure = true; 
                                        singlebracket = false;
                                    end                                    
                                end

                            end
                        end
                end
                set(disp1, 'String', str);
                
            case 'perc'
%                 procenta, zmeni posledni sub vyraz na procenta
                str = get(disp1, 'String');
                [temp,lcount] = size(strfind(str, '('));
                [temp,rcount] = size(strfind(str, ')'));
                for i=2:n
                    if(ismember(str(i), list))
                       signcount = signcount+1; 
                    end
                end
%                 zmena pokud neni vyraz dokoncen, tzn jedna se o zmenu
%                 subvyrazu
                if not(str=="") && not(ismember(str(end),list)) && not(str(end)=='(')
                    if lcount == 0
                    n = length(str);
                    lastsignpos = 0;
                    for i = 1:n
                        if(ismember(str(i), list))
                            lastsignpos = i;
                        end
                    end
                    s = str(lastsignpos+1:end);
                    s = str2double(s);
                    s = s/100;
                    s = num2str(s);
                    
                    str = str(1:lastsignpos);
                    str = insertAfter(str, lastsignpos, s);
                    set(disp1, 'String', str);
                    else
                        rbrcount = 0;
                        lbrcount = 0;
                        for k=n:-1:1
                            if str(k) == ')'
                                rbrcount = rbrcount+1;
                            elseif str(k) == '('
                                lbrcount = lbrcount+1;
                            end
                            if rbrcount == lbrcount
                                s = str(k:n);
                                s = eval(s);
                                s = s/100;
                                s = num2str(s);
                                str = str(1:k-1);
                                str = insertAfter(str, k-1, s);
                                set(disp1, 'String', str);
                                return;
                            end
                        end
                    end
                    
%                     pokud menime cely vyraz
                elseif(signcount>0 && rcount == lcount)
                    str = eval(str);
                    str = str/100;
                    str = num2str(str);
                    set(disp1, 'String', str);                    
                end
                
%                 vyraz na druhou
            case 'sq'
%                 jedna se pouze o vlozeni ^2 za sub vyraz
                str = get(disp1, 'String');
                n = length(str);
                %mocniny komplex cisel
                if (not(str == "") && str(end) == 'i')
                    str = eval(str);
                    str = str^2;
                    set(disp1, 'String', str);
                    
                elseif not(str=="") && not(ismember(str(end),list))
                    str = insertAfter(str, n, '^2');
                    set(disp1, 'String', str);
                    signcount = 0;
                end
%                 odmocnina z vyrazu
            case 'sqrt'
                str = get(disp1, 'String');
                n = length(str);
                for i=2:n
                    if(ismember(str(i), list))
                       signcount = signcount+1; 
                    end
                end
%                 pokud vyhodnocujeme jednoduche cislo tak rovnou vypocti
                if (signcount==0 && not(str==""))
                    str = eval(str);
                    str = sqrt(str);
                    str = num2str(str);
                    set(disp1, 'String', str);
                    signcount = 0;
%                     sqrt nelze vlozit pokud pred ni neni znamenko nebo
%                     leva zavorka
                elseif (n > 0 &&(not(ismember(str(end),list))) && not(str(end)=='('))
                    return;
%                     jinak vloz sqrt( jako subvyraz
                else
                    str = insertAfter(str, n, 'sqrt(');                    
                    set(disp1, 'String', str);
                    signcount = 0;
                end
%                 obracena hodnota vyrazu
            case 'inv'
                str = get(disp1, 'String');
                n = length(str);
                lastsignpos = 0;
%                 zjisti pocet znamenek a pozici posledniho znamenka
                for i=2:n
                    if(ismember(str(i), list))
                       signcount = signcount+1;
                       lastsignpos = i;
                    end
                end
                                
                [temp,lcount] = size(strfind(str, '('));
                [temp,rcount] = size(strfind(str, ')'));
%                 pokud se jedna o subvyraz
                if not(str == "0") && not(isempty(str)) && not(ismember(str(end),list)) ...
                        && signcount>0 || dotcount>0
%                     pokud nejsou zavorky vyhodnot pouze posledni cislo
                    if rcount == 0
                        s = str(lastsignpos+1:end);
                        str = str(1:lastsignpos);
                        s = str2double(s);
                        if s == 0
                           er = 'Division by zero!';
                           set(disp1, 'String', er);
                           pause(2);
                           set(disp1, 'String', "");
                           return;
                        end
                        s = 1/s;
                        s = num2str(s);
                        str = insertAfter(str, lastsignpos, s);
                        set(disp1, 'String', str);
                        return;
%                         pokud jsou ve vyrazu zavorky, vyhodnot nejblizsi
%                         uzavrenou zavorku
                    else
                        lbrcount = 0;
                        rbrcount = 0;
                        for k = n:-1:1
                           if str(k) == '('
                               lbrcount = lbrcount+1;
                           elseif str(k) == ')'
                               rbrcount = rbrcount+1;
                           end
                           if lbrcount == rbrcount
                                s = str(k:n);
                                str = str(1:k-1);
                                s = eval(s);
                                if s == 0
                                    er = 'Division by zero!';
                                    set(disp1, 'String', er);
                                    pause(2);
                                    set(disp1, 'String', "");
                                    return;
                                end
                                s = 1/s;                                
                                s = num2str(s);
                                str = insertAfter(str, k-1, s);
                                set(disp1, 'String', str);
                                return;
                           end                                
                        end
                    end
                    str = eval(str);
                    if(str==0)                        
                        er = 'Division by zero!';
                        set(disp1, 'String',er);
                        pause(2);
                        set(disp1, 'String', "");
                        return;
                    end
                    str = 1/str;                    
                    set(disp1, 'String', str);
%                     pokud je pouze nula
                elseif(str=="0")
                    er = 'Division by zero!';                    
                    set(disp1, 'String',er);
                    pause(2);
                    set(disp1, 'String', "");
%                     pokud je pouze jednoduche cislo
                elseif(not(str == "") && signcount == 0)
                    str = eval(str);
                    str = 1/str;
                    set(disp1, 'String',str);
                end
                signcount = 0;
                                
%                 smaz posledni
            case 'back'
                str = get(disp1, 'String');
                n = length(str);
                if (str~="")
%                     smazani mocniny, odmocniny, znamenka, chybove hlasky
                    if(n>=2 && str(end-1) == '^')
                        str = str(1:end-1);
                    elseif(n>=5 && str(end-4) == 's')
                        str = str(1:end-4);
                    elseif(ismember(str(end),list))
                        signcount = signcount-1;
                    elseif(str(end) == '!')
                        set(disp1, 'String', '');
                        return;
                    end
%                     mazani ostatnich znaku
                    str = str(1:end-1);
                end
                set(disp1, 'String', str);
%                 rovna se
            case 'equ'
                str = get(disp1, 'String');
                [temp,lcount] = size(strfind(str, '('));
                [temp,rcount] = size(strfind(str, ')'));
%                 najdi pocet deleni nulou
                [temp,zerodivcount] = size(strfind(str, '/0'));
                [temp,falsezerodivcount] = size(strfind(str, '/0.'));
                zerodivcount = zerodivcount - falsezerodivcount;
%                 vyhodnot je li to mozne
                if not(str=="") &&(zerodivcount == 0) && not(ismember(str(end), list)) && lcount == rcount   
                    str = eval(str);
                    set(disp1, 'String', str);
                    signcount = 0;
                    dotcount = 0;
%                     neni li to mozne nedelej nic
                elseif(str=="" || ismember(str(end),list) || lcount~=rcount)
                    set(disp1, 'String', str);
%                     jinak se jedna o deleni nulou
                else
                    er = 'Division by zero!';
                    set(disp1, 'String', er);
                    signcount = 0;
                    dotcount = 0;
                    pause(2);
                    set(disp1, 'String', "");
                end
%                 nula
            case 'zer'
                str = get(disp1, 'String');
                n = length(str);
%                 if str == ""
%                 neni mozne psat nulu za ( ) ^2    
                if (n > 1) && ( str(end) == '(' ...
                        || str(end) == ')' || str(end-1) == '^')
                    return;
%                     neni mozne psat dve nuly za znamenko (umoznuje psat
%                     desetinna cisla
                elseif (n>1) && (ismember(str(end-1),list)) && (str(end) == '0')
                    return;
%                neni mozne psat vic nez jednu nulu na zacatek (des cisla)     
                elseif (n==1) && str(end) == '0'
                    return;
                else
                   str = strcat(str, names{strcmp(src.Tag, names1)});
                   set(disp1, 'String', str);
                end                                                
            otherwise
%                 pocet levych a pravych zavorek ve vyrazu
                str = get(disp1, 'String');
                [temp,lcount] = size(strfind(str, '('));
                [temp,rcount] = size(strfind(str, ')'));
%                   delka stringu
                    n = length(str);
                signcount = 0;    
               

%                 specialni pripad psani prvniho znaku
                if (str == "")  %prvni znak
                    str = strcat(str, names{strcmp(src.Tag, names1)});
%                     unarni minus
                    if(str=="-")
                        set(disp1, 'String', str);
%                         nelze jinak zacit znamenkem
                    elseif(ismember(str(end), list) || str(end) == ')' || str(end) == '.')
                        str(end) = [];   
                    end
                    set(disp1, 'String', str);
                    
%                     souhlasi-li pocet zavorek                
                elseif(lcount>=rcount)
                    str = strcat(str, names{strcmp(src.Tag, names1)});
%                     set(disp1, 'String', str);
                    lastchar = str(end-1);
                    for i=2:n
                        if(ismember(str(i), list))
                            signcount = signcount+1; 
                        end
                    end
%                     mam-li dve znamenka po sobe zmen hodnotu
%                     predposledniho na posledni
%                     pokud je tam jen unarni minus tak nelze vlozit jine
%                     znamenko
                    

                    if ((n==1) && (str=="-"))
%                         return;
                    end
%                     za nulu se da napsat jen znamenko nebo desetinna
%                     carka
                    if ((str(end-1) == '0') && not(ismember(str(end),list))&& not(str(end) == '.'))
                        str = str(1:end-1);
                        set(disp1, 'String', str);
                        %return;
                    end
%                     za */ se da vlozit pouze -
                     if(str(end) == '-' && (lastchar == '*' || lastchar == '/'))
                         set(disp1, 'String', str);
%                      jinak nahrad znamenkem, pokud to neni pripad /- *-
                     elseif(ismember(lastchar,list) && ismember(str(end), list) && not(ismember(str(end-2),list))) 
                        str(end-1) = str(end);
                        str(end) = [];
                        n = n-1;
                        set(disp1, 'String', str);
%                         pokud /- *- a vkladal bych dalsi znamenko nedelej nic
                     elseif (n>2 && ismember(str(end),list)&& ismember(str(end-1),list) && ismember(str(end-2),list))
                         return;
                    end
                    
%                     pocet desetinnych tecet ve vyrazu
                    [temp,dotcount] = size(strfind(str, '.'));
                    
%                   
%                     nalezni pozici posledniho znamenka
                    lastsignpos = 0;
                    for i = 1:n
                        if(ismember(str(i), list))
                            lastsignpos = i;
                        end
                    end
%                     tecek je technicky tolik, kolik je tam znamenek
                   dotcount = signcount; 
%                    tecka muze byt v prnim cisle bez znamenka nebo se taky
%                    uz muze nachazet v poslednim zadanem cisle pro ktere
%                    testujeme zda jeste jde napsat tecku
                    n = length(str);
                    for j = lastsignpos+1:n
                        if(str(j) == '.')
                            dotcount = dotcount+1;
                        end
                    end
%                     je mozno napsat tolik carek, kolik je cisel tedy
%                     cisel oddelenych znamenkem+1
                    if (dotcount >signcount+1)
                        str = str(1:end-1);
                        set(disp1, 'String', str);
                    end

%                     neni mozne napsat vice pravych zavorek nez levych
%                     zavorek
                   [temp,lcount] = size(strfind(str, '('));
                    [temp,rcount] = size(strfind(str, ')'));
                    
%                     kontroluje pocet zavorek, nelze napsat zavorky hned
%                     vedle sebe - prazdne zavorky, dale musi byt napsane
%                     znaminko pred ( a po ) ale ne po ( a pred )
                    if( rcount>lcount || (str(end-1) == '(') && (str(end) == ')')...
                            || (str(end-1) == '(')  &&  ismember(str(end), list) && not(str(end)=='-')...
                            || (str(end) == '(') && (not(ismember(str(end-1), list))) && not(str(end-1)=='(')...
                            || str(end) == ')' && ismember(str(end-1), list)...
                            || str(end-1) == ')' && (not(ismember(str(end), list))) && not(str(end) ==')'))
                        str = str(1:end-1);
                    end

                   set(disp1, 'String', str); 
                   
                   signcount = 0;
                   dotcount = 0;
                end
        end
    end
% vycisti display
    function clear_callback(varargin)
        set(disp1, 'String', '');
    end
end
        