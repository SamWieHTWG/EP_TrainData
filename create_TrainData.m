%% This program is written to create Training Data for the EP Project

% author: Samuel Wiertz, wiertzsamuel@gmail.com
% date: 16.12.2018

close all


%% path definition

% define actual path
actual_path = pwd;

% add function directory
addpath([actual_path '/functions'])

% add data directory
addpath([actual_path '/data'])

% add C Code directory
addpath([actual_path '/C_mex'])

%% initialize parameter
Ts = 0.01;

%% start endless creation loop
while(1)
    
    % get random PT-2 data
    [ num, denom, n_cont, d_cont] = create_random_PT2(Ts);
    
    % create function handle for cost function
    
    
end    

