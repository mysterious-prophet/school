%obdelnik
classdef obdeln1 < handle
    properties(Access = 'public')
        wid
    end
%     properties(GetAccess = 'private', SetAccess = 'private')
%         wid
%         hei
%     end
    events
        fplocha;
    end
    methods
        function obj = obdeln1(a,b )
            obj.wid = a;
            obj.hei = b;
        end
%         function( 
%             
%         end
        function S = plocha(obj)
            addlistener(obj, 'fplocha', @hudba);
            nofify(obj, 'fplocha');
            S = obj.wid*obj.hei;
        end
        function obj = widchange(obj, wid)
            obj.wid = wid;
        end
        function obj = hudba(obj, ~)
%             load handel;
%             sound (y, Fs);
            load handel;
            player = audioplayer(y, Fs);
            play(player);
        end
        

        function drawobdeln(obj, varargin)
            n = length(varargin);
            switch n
            case 0
                x = [0 obj.wid obj.wid 0 0];
                y = [0 0 obj.hei obj.hei 0];
                plot(x, y);
                axis equal off;

            case 1
                c = varargin{1};
                x = [0 obj.wid obj.wid 0 0] + c(1);
                y = [0 0 obj.hei obj.hei 0] + c(2);
                plot(x, y);
                axis equal
                xlabel('\it x');
                ylabel('\it y');
                title('obraz obdelniku');
%                 axis([0 2*c(1) + obj.wid 0 2*c(2) + obj.hei]);
            case 2
                c = varargin{1};
                color = varargin{2};
                x = [0 obj.wid obj.wid 0 0] + c(1);
                y = [0 0 obj.hei obj.hei 0] + c(2);
                fill(x, y, color);
                axis equal
                xlabel('\it x');
                ylabel('\it y');
                title('obraz obdelniku');
                axis([0 2*c(1) + obj.wid 0 2*c(2) + obj.hei]);
            end
        end
    end
end