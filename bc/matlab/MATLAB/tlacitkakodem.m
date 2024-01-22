function tlacitkakodem
clear, clc, close
h=figure('units', 'normalized', 'position', [0.05 0.5 0.4 0.3], ...
    'MenuBar', 'none', 'NumberTitle', 'off', 'Resize', 'off');
h0=uicontrol('Style', 'pushbutton', 'units', 'normalized', 'position',...
   [0.05 0.75 0.2 0.1], 'String', 'Insert file', 'FontSize',14,'FontWeight', 'bold',...
   'BackGroundColor','g');
h1 = uicontrol ('Style', 'pushbutton', 'units', 'normalized', 'position',...
   [0.05 0.5 0.2 0.1], 'String', 'Play', 'FontSize',14,'FontWeight', 'bold',...
   'BackGroundColor','y','Callback', @playcallback);
h2=uicontrol('Style', 'pushbutton', 'units', 'normalized',...
    'position', [0.05 0.25 0.2 0.1], 'String', 'Stop', 'FontSize', 14,...
'FontWeight', 'bold', 'BackGroundColor', 'm', 'Callback', @stopcallback);

inputtext=uicontrol('Style', 'edit', 'units', 'normalized', 'position',...
   [0.35 0.75 0.5 0.1], 'FontSize',14,'FontWeight', 'bold',...
   'BackGroundColor','w');



    function playcallback (varargin)
        c=get(inputtext, 'String');
        [y, Fs]=audioread(c);
        sound(y, Fs);
    end

    function stopcallback(varargin)
        clear sound;
        set(inputtext, 'String', '');
    end
end