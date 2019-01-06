
close all

% test speed
tic

for ii = 1:10000
   simulate_error_mex(single([0.1 0.1]),single([-1 0]),single([1 0]),single([-0.3 -0.01]));

end

toc

% test functionality

num_c = [ 0.1 0.1];
den_c = [-1 0];

num_p = [1 0];
den_p = [ -0.2 -0.2];


sys_c = tf(num_c,[1 den_c], 0.01);
sys_p = tf(num_p,[1 den_p], 0.01);

ol = sys_c * sys_p;
sys = ol / ( 1 + ol);

figure
step(sys)


% figure
% step(sys,10)
y = step(sys,10000);
error = sum((y-1).^2);

error_mex =    simulate_error_mex(single(num_c),single(den_c),single(num_p),single(den_p));


error - error_mex
% offset = 1. That's okay, optimum of cost function remains same


