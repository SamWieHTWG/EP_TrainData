
close all
clearvars

% get paths
curr_path = pwd;
cd ..
folder = pwd;
addpath(genpath(folder));
cd(curr_path);


%% load up to now - data
prev_data = load('data.mat');
data = prev_data.data;


for ii =  1: length(data(:,1))
    
    
    P = data(ii,1);
    I = data(ii,2);
    
    num = data(ii,3:4);
    den = data(ii,5:7);
    
    % PI - controller:
    % P + I/s 
    
    % test
    %P = P+100000;
    %I = I +1000;
%     
%     P = [[126.81487589]]
%     I = [[76.39182983]]
%     num = [ 8.37711424 16.60857845]
%     den = [ 1. 6.57017903 16.60857845]
%     
    sys_p = tf([P],1);
    sys_i = tf([I],[1 0]);
    
    sys_c = sys_p + sys_i;
    sys_pt2 = tf(num,den);
    
    %ol_num = conv(num, [P I])
    %ol_den = conv(den, [1 0])
    ol = sys_c*sys_pt2;
    
    %sys_num = ol_num
    %sys_den = ol_den + [0,ol_num]
    sys = ol/(1+ol);
    %sys2 = tf([1062.34270231 2746.15790012 1268.7596987 ], [1.0, 1068.9128813367643, 2762.7664785678744, 1268.7596987023992])
    
    close all
    figure
    step(sys)
    %hold
    %step(sys2,'x')
    %step(tf(sys_num, sys_den))
    pause(1)
    
end

