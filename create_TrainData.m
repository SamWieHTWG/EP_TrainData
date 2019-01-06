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

% sample Time
Ts = 0.01;

% optimization parameters
lb_P = 1E-4;
ub_P = 50;
lb_I = 0;
ub_I = 100;
grid_samples = 700; % grid search duration for 100*100 values about 1 sec.




%% start endless creation loop
while(1)
    
    % get random PT-2 data
    [ num_p, den_p, n_cont, d_cont] = create_random_PT2(Ts);
    
    
    
    %% Test
    if (0)
       
       P = 0.1; lb_P = P; ub_P = P;
       I = 0.2; lb_I = I; ub_I = I;

        num_p = [1 0.1];
        den_p = [ 0.9 0 ];
        
        
    end
    %%
    
    
    % create function handle for cost function
    fun_handle = @(P,I) cost_function(P,I, num_p, den_p, Ts);
    
    % grid search
    tic
    [x_best, J_best] = grid_search(fun_handle, lb_I, ub_I, lb_P, ub_P, grid_samples)
    toc
    
    %break 
end    

