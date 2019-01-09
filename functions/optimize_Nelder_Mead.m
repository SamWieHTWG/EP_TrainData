function [x_best] = optimize_Nelder_Mead(x0,fun_handle)

% this function improves the grid search result by finding the local
% minimum in the area of the grid search result

% more details about the alogrithm:
% https://en.wikipedia.org/wiki/Nelder%E2%80%93Mead_method

% author: Samuel Wiertz
% date: 10.01.2019

% inputs: 
% f = cost function handle
% x0 = starting point of iterative computation

f = @(x)fun_handle(x(1),x(2)); % change to vector-

alpha = 1;
beta = 0.8;
gamma = 1.2;

iteration = 1;

Theta = [x0 + 0.2* x0;
          x0;
          x0 - 0.2* x0];
      
n = length(Theta(:,1));
J = zeros(n,1);

J_start = f(x0);

while iteration < 300
    
    
    J(1) = f(Theta(1,:));
    J(2) = f(Theta(2,:));
    J(3) = f(Theta(3,:));
    
    [J_h,i] = max(J);
    Theta_h = Theta(i,:);
    [J_l,k] = min(J);
    Theta_l = Theta(k,:);
    
    
    Theta_help = Theta;
    Theta_help(i,:)=[]; % Theta zu Maxmimum rausnehmen
    J_help=J;
    J_help(i)=[];
    
    [J_sec, ~] = max(J_help);
    
    Theta_0 = mean(Theta_help); % Mitte zwischen zwei kleineren Theta
    
    
    Theta_r = Theta_0 + alpha * (Theta_0-Theta_h);
    J_hat = f(Theta_r);
    
    if( J_sec > J_hat && J_hat >= J_l)
        
        Theta(i,:) = Theta_r; % Theta0 = neues Simplex
        
    elseif(J_hat<J_l)
        
        Theta_tilde = Theta_0+ gamma*(Theta_r-Theta_0);
        J_tilde = f(Theta_tilde);
        if J_tilde <= J_hat
            Theta(i,:) = Theta_tilde;
        else
            Theta(i,:) = Theta_r;
        end
    elseif (J_hat>=J_sec)
        
        Theta_tilde = Theta_0+ beta*(Theta_h-Theta_0);
        J_tilde = f(Theta_tilde);
        
        if J_tilde < J_h
            Theta(i,:) = Theta_tilde;
        else % shrink
            %disp('reset')
            
            for ii=1:n
                if (ii~=k)
                    Theta(ii,:) = Theta(ii,:)+1/2 * (Theta(ii,:)-Theta_l);
                end
            end
            
        end
        
        
    else
        % shrink
        for ii=1:n
            if (ii~=k)
                Theta(ii,:) = Theta(ii,:)+1/2 * (Theta(ii,:)-Theta_l);
            end
        end
    end
    
    %J_line = mean(J);
    
    %value = var(J);
    iteration = iteration +1;
    
    %Theta_save(iteration,:)= Theta_r;

end
   x_best = Theta_r;
    
   if J_hat > J_start
       disp('No improvement by Nelder Mead');
        x_best = x0;
   end
   
end



