function [num, den] = discretize_PT2(n_cont, d_cont, Ts)

% author : Samuel Wiertz
% date   : 20.12.2018

% this function discretizes a continous transfer function of a PT2 plant 
% to a discrete one

% cont tf: b1s + b0) / (s²+a1s+a0)

% Euler Vorwaerts : s = (z-1/T)


if d_cont(1) ~= 1
    error(' normalize input');
end


b1 = n_cont(1);
b0 = n_cont(2);

a1 = d_cont(2);
a0 = d_cont(3);

b1_d = Ts * b1;
b0_d = b0 * Ts^2 - b1 * Ts;

a1_d = Ts * a1 - 2 ;
a0_d = Ts^2 * a0 - Ts * a1 +1;

num = [b1_d, b0_d];
den = [1 a1_d a0_d];


%% funtion was tested succesfully!

end

