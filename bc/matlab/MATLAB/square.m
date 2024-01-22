classdef square < obdeln1
    properties
        Property1
    end
    methods
        function obj = square(a)
            obj = obj@obdeln1(a, a);
        end
%         function outputArg = medthod1(obj, inputArg)
%             outputAtd = obj.Property1 + inputArg;
%         end
    end
end