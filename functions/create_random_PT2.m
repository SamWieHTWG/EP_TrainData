function [ num, denom, n_cont, d_cont] = create_random_PT2(Ts)

% author: Samuel Wiertz
% date: 04.01.2019

% This function creates the numerator and denominator of 
% a discrete pt-2 plant with sample time = 0.01

% output: num, denom = discrete plant values
%         n_cont, d_cont = continous plant values

pole1 = (rand-0.5) * 20;  % pole lays between -10 and 10
pole2 = (rand-0.5) * 20;  % smallest time constant = 0.1 s = sufficient

pole1 = -2;
pole2 = 3;

% calculation of transfer function of system
d_cont = [1 -pole1+-pole2 -pole1*-pole2];
n_cont = [rand rand];

% calculation of dc gain and normalize numeartor
dc_gain = n_cont(2) / d_cont(3);    
n_cont = n_cont / dc_gain;

% discretize
[num, den ] = discretize_PT2(n_cont, d_cont, Ts);

denom = den(2:end);


end

