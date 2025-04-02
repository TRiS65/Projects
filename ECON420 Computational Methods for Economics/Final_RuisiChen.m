clear;clc
% README: functions are at the end of this document
%% 
% *1 Solve the Maximization Problem*

z=3; alpha=0.33;beta=0.96;sigma=2;n=50;
Rngk = [0.01,2];

%tic
k_nodes = linspace(Rngk(1),Rngk(2),n)';
basis = fundefn('spli',n,Rngk(1),Rngk(2),3);

f = @(k) z*k.^alpha;
f_prime = @(k) alpha*z*k.^(alpha-1);
u_prime = @(c) c.^(-sigma);
k_next = @(k,a) f(k) - funeval(a,basis,k);
Resid = @(k,a) beta*(u_prime(funeval(a,basis,k_next(k,a)))./u_prime(funeval(a,basis,k))).*f_prime(k_next(k,a))-1;
F = @(a) Resid(k_nodes,a);

a0 = 0.7.*f(k_nodes);
a_hat = fsolve(F,a0,optimset('Display','off'))
%toc
%% 
% *2 Check the Solution*

sigma = 1.000001; 

f = @(k) z*k.^alpha;
f_prime = @(k) alpha*z*k.^(alpha-1);
u_prime = @(c) c.^(-sigma);
k_next = @(k,a) f(k) - funeval(a,basis,k);
Resid = @(k,a) beta*(u_prime(funeval(a,basis,k_next(k,a)))./u_prime(funeval(a,basis,k))).*f_prime(k_next(k,a))-1;
F = @(a) Resid(k_nodes,a);

a_hat2 = fsolve(F,a0,optimset('Display','off'))

k_fine = linspace(Rngk(1),Rngk(2),1000)';
k_star = @(k) alpha*beta*z*k.^alpha;
k_star_hat = @(k) f(k) - funeval(a_hat2,basis,k);
plot(k_fine,k_star_hat(k_fine),k_fine,k_star(k_fine))

maxDiff = max(abs(k_star_hat(k_fine)-k_star(k_fine)))
%% 
% *3   Time Path of Capital*

k0 = 0.1;
T = 15;

sigma1 = 2

tic
f = @(k) z*k.^alpha;
f_prime = @(k) alpha*z*k.^(alpha-1);
u_prime = @(c) c.^(-sigma1);
k_next = @(k,a) f(k) - funeval(a,basis,k);
Resid = @(k,a) beta*(u_prime(funeval(a,basis,k_next(k,a)))./u_prime(funeval(a,basis,k))).*f_prime(k_next(k,a))-1;
F = @(a) Resid(k_nodes,a);
a_hat1 = fsolve(F,a0,optimset('Display','off'))
k_star_hat1 = @(k) f(k) - funeval(a_hat1,basis,k);
TimePath1 = TimePath(k_star_hat1,T)
toc

sigma2 = 0.5

tic
f = @(k) z*k.^alpha;
f_prime = @(k) alpha*z*k.^(alpha-1);
u_prime = @(c) c.^(-sigma2);
k_next = @(k,a) f(k) - funeval(a,basis,k);
Resid = @(k,a) beta*(u_prime(funeval(a,basis,k_next(k,a)))./u_prime(funeval(a,basis,k))).*f_prime(k_next(k,a))-1;
F = @(a) Resid(k_nodes,a);
a_hat2 = fsolve(F,a0,optimset('Display','off'))
k_star_hat2 = @(k) f(k) - funeval(a_hat2,basis,k);
TimePath2 = TimePath(k_star_hat2,T)
toc

Time = linspace(1,15,15);
plot(Time,TimePath1,Time,TimePath2)
%% 
% *Functions*
% 
% 3 run for T periods

function [K] = TimePath(k_star_hat,T)
    K = zeros(T,1);
    K(1) = 0.1;
    for t = 2:T
        K(t) = k_star_hat(K(t-1));
    end
end