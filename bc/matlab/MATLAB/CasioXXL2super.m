function CasioXXL2super
clear; clc; close all
h = figure('Units', 'Normalized', 'Position', [0.05 0.5 0.32 0.38], 'Name',...
    'CasioXXL', 'NumberTitle', 'off', 'MenuBar', 'None', 'Resize', 'off');
disp1 = uicontrol('Units', 'Normalized', 'Style', 'Text', 'Position', ...
    [0.05 0.75 0.6 0.15], 'String', '', 'FontSize', 24, 'FontWeight', 'bold',...
    'BackgroundColor', 'white', 'Tag', 'mmonit', 'HorizontalAlignment'...
    , 'right');

names = {'7', '8', '9', '+', '.', '4', '5', '6', '-', '+/-', '1', '2', '3', '*', 'sqrt',...
    '0', '(',')', '/', '='};
m = 4; n = length(names)/m;
names1 = {'sev', 'eig', 'nin', 'plu', 'dec', 'fou', 'fiv', 'six' , 'sub', 'sig',...
    'one', 'two', 'thr', 'mul', 'sq', 'zer', 'lbr', 'rbr', 'div', 'equ'};

wi = 0.14; he = 0.12;
mw = 0.05; mh = 0.03;
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

uicontrol('Units', 'Normalized', 'Style', 'pushbutton', 'Position', ...
    [0.7 0.75 0.25 0.15], 'String', 'CLEAR', 'FontSize', 21, ...
    'FontWeight', 'bold', 'Tag', 'clear', 'Callback', @clear_callback);
hp1 = uipanel(h, 'Units', 'Normalized', 'Position', [0.04 0.74 0.62 0.17]);
uistack(hp1, 'bottom');
hp2 = uipanel(h, 'Units', 'Normalized', 'Position', [0 0 1 1]);
uistack(hp2, 'bottom');
    function bigcallback(src, ~, ~)
        switch src.Tag
            case 'sig'
                str = get(disp1, 'String');
                str = strcat('-', str);
                set(disp1, 'String', str);
            case 'sq'
                str = get(disp1, 'String');
                s = str2double(str);
                s = num2str(sqrt(s));
                set(disp1, 'String', s);
            case 'equ'
                str = get(disp1, 'String');
                str = eval(str);
                set(disp1, 'String', str);
            case 'zer'
                str = get(disp1, 'String');
                if (str == '0')
                    
                else
                   str = strcat(str, names{strcmp(src.Tag, names1)});
                   set(disp1, 'String', str);
                end                                                
            otherwise
                list = ['+', '-', '*', '/', '.'];
                str = get(disp1, 'String');
                lcount = size(strfind(str, '('));
                rcount = size(strfind(str, ')'));
                if (str == "")  %prvni znak
                    str = strcat(str, names{strcmp(src.Tag, names1)});
                    if(ismember(str(end), list) || str(end) == ')')
                        str(end) = [];   
                    end
                    set(disp1, 'String', str);
                elseif(lcount>=rcount)
                    str = strcat(str, names{strcmp(src.Tag, names1)});
                    set(disp1, 'String', str);
                    lastchar = str(end-1);
                    if(ismember(lastchar,list) && ismember(str(end), list)) 
                        str(end-1) = str(end);
                        str(end) = [];
                        set(disp1, 'String', str);
                    end
                
                end
                
        end
    end
    function clear_callback(varargin)
        set(disp1, 'String', '');
    end
end
        