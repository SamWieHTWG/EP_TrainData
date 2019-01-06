function [x_best, J_best] = grid_search(f, lb_I, ub_I, lb_P, ub_P, n_values)



% this function executes a grid search to find good starting points
% for the optimization

% author: Samuel Wiertz
% date: 05.01.2019

% inputs: lb_I,ub_I,lb_P, ub_P = lower / upper bound of grid
% f = cost function handle
% n_values = number of samples 

J_best = 1E4;
x_best = zeros(2,1);

index(1,:) = linspace(lb_P, ub_P, n_values);
index(2,:) = linspace(lb_I, ub_I, n_values);

for ii = index(1,:) % for all values of P
    
    for kk = index(2,:) % for all values of I
        
        
        J = f(ii,kk);
        
        if J < J_best
            
            J_best = J;
            x_best = [ii, kk];     
        end
    end
    
end





end

