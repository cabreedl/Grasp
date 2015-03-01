function [zcr] = ZCR(x)
%ZERO CROSSING: Tracks the number of times the signal crosses y=0 

zcr = 0;
for i = 1:length(x)-1 
    if ((x(i)>=0 && x(i+1)<0) || (x(i)<=0 && x(i+1)>0))
        zcr = 1+zcr;
    end
end

% Normalizes returned values to zero crosses per 100ms
norm_fact = length(x)/100;  
zcr = round(zcr/norm_fact);

end

