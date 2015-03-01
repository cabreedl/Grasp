function [feature_vector] = Extract_RMS(x,nChan)

feat_rms = zeros(1,4);

for i = 1:nChan
    feat_rms(1,i) = rms(x(:,i));
end

feature_vector = feat_rms;
end

