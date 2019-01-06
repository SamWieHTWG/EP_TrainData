function [ J ] = cost_function(P,I, num_p, den_p, Ts)

% This function evaluates a given set of control parameters (P,I)
% for a given PT-2 plant

% author: Samuel Wiertz
% date: 21.12.2018

% input:    P, I = control parameters
%           num_p, den_p = numerator / denominator of discretized PT2-plant


%% calculation of controller transfer function from P, I
D = 0;  % no D - part  to begin with, possibly later

p1 = P+I*Ts/2+D/Ts;
p2 = -P+I*Ts/2-2*D/Ts;
p3 = D/Ts;

c_num = [p1 p2 p3];
c_den = [1 -1 0];



end

