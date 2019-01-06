function [ J ] = cost_function(P,I, num_p, den_p, Ts)

% This function evaluates a given set of control parameters (P,I)
% for a given PT-2 plant

% author: Samuel Wiertz
% date: 21.12.2018

% input:    P, I = control parameters
%           num_p, den_p = numerator / denominator of discretized PT2-plant


%% calculation of controller transfer function from P, I

p1 = P;
p2 = -P+I*Ts;

num_c = [p1 p2];
den_c = [1 -1];


J = simulate_error_mex(single(num_c),single(den_c),single(num_p),single(den_p));


end

