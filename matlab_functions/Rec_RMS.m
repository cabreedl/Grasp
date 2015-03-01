function [] = Rec_RMS(test_file)

fs = 1000;
data = load(test_file);
proto_M = load('Prototype_RMS_Mean.txt');
proto_S = load('Prototype_RMS_Std.txt');
wLen = 200;
nFeat = 4;
nClass = 4;
mClass = 0;
tClass = 0;
tThresh = 190;
D = zeros(length(data)-wLen,5);
Classification = [];
for n = wLen:length(data)    
    x = data(n-(wLen-1):n,:);
    FeatVect = Extract_RMS(x);
    d_j = [0,0,0,0];    
    for j = 1:nClass
        pt1 = 0;
        pt2 = 0;
        for i = 1:nFeat
           pt1 = pt1 + (((FeatVect(i) - proto_M(j,i))^2)/(proto_S(j,i)^2));
           pt2 = pt2 + log(proto_S(j,i)^2);
        end
        d_j(j) = pt1 + pt2; 
    end
    if min(d_j) == d_j(1)
        %classify as HC
        if 1 ~= mClass 
            % Notify of classification change
            if n - tClass > tThresh
                tClass = n;
                mClass = 1;
                t = n/fs;
                Class = sprintf('HC @ Time %06.3f seconds',t);
                fprintf('%s\n',Class);
                Classification = vertcat(Classification,Class);
            end
        end          
    elseif min(d_j) == d_j(2)
        %classify as HO
        if 2 ~= mClass 
            % Notify of classification change
            if n - tClass > tThresh
                tClass = n;
                mClass = 2;
                t = n/fs;
                Class = sprintf('HO @ Time %06.3f seconds',t);
                fprintf('%s\n',Class);
                Classification = vertcat(Classification,Class);
            end
        end        
    elseif min(d_j) == d_j(3)
        %classify as WF
        if 3 ~= mClass 
            % Notify of classification change
            if n - tClass > tThresh
                tClass = n;
                mClass = 3;
                t = n/fs;
                Class = sprintf('WF @ Time %06.3f seconds',t);
                fprintf('%s\n',Class);
                Classification = vertcat(Classification,Class);
            end
        end           
    elseif min(d_j) == d_j(4)
        %classify as WE
        if 4 ~= mClass 
            % Notify of classification change
            if n - tClass > tThresh
                tClass = n;
                mClass = 4;
                t = n/fs;
                Class = sprintf('WE @ Time %06.3f seconds',t);
                fprintf('%s\n',Class);
                Classification = vertcat(Classification,Class);
            end
        end         
    end
    D(n,:) = [n,d_j(1),d_j(2),d_j(3),d_j(4)];
%     if pClass~=mClass
%          fprintf('%s\n',Class);
%     end
end
% xlswrite(title,Classification);
end