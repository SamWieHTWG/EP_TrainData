
close all

% get paths
curr_path = pwd;
cd ..
folder = pwd;
addpath(genpath(folder));
cd(curr_path);

% test functionality

P = 0.1;
I = 0.1;

Ts = 0.01;
T = Ts;

num_p = [1 0.1];
den_p = [ 0.9 0 ];


[ J ] = cost_function(P,I, num_p, den_p, Ts)

p1 = P;
p2 = -P+I*Ts;

num_c = [p1 p2];
den_c = [1 -1];


sys_c = tf(num_c,[den_c], T);
sys_p = tf(num_p,[1 den_p], T);


ol = sys_c * sys_p;
sys = feedback(ol,1) %ol / ( 1 + ol);

figure
step(sys)


% figure
% step(sys,10)
y = step(sys,10000);
error = sum((y-1).^2)


