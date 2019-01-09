
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
    
    sys_p = tf([P],1);
    sys_i = tf([I],[1 0]);
    
    sys_c = sys_p + sys_i;
    sys_pt2 = tf(num,den);
    
    ol = sys_c*sys_pt2;
    
    sys = ol/(1+ol);
    
    close all
    figure
    step(sys)
    pause(1)
    
end

