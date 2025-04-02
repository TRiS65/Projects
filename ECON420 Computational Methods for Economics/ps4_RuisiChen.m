clear;clc
% README: functions are at the end of this document
%% 
% *2.1    Function g and Parameters*

% Parameters
Nbar = 24;
A = 2;
alpha = 0.33; 
epsilon = 1.9;
sigma = 2;
psi = 2;

g = @(ne) RHSequ(ne,Nbar,A,alpha,epsilon,sigma,psi);

X = linspace(0,24,100);
plot(X,g(X),X,X)

% using f(ne) = g(ne)-ne = 0 to solve for ne
f = @(ne) g(ne) - ne; 
%% 
% *2.2    Function Iteration Method*

Tol = 1e-6;
x0 = 0;
X2 = FunIterMethod(g,x0,Tol)
%% 
% *3   Bisection Method*

a = 0; 
b = 24;
x3 = BisectionMethod(f,a,b,Tol)
%% 
% *4   fsolve*

x4 = fsolve(f,x0)
%% 
% *6   Methods Compare*
% 
% a = 0 , b = 24

[time_B,time_f] = runTime(f,100,x0,Tol,0,24);
BisectionTime = mean(time_B)
fsolveTime = mean(time_f)
%% 
% a = -100 , b = 100

[time_B_100,time_f_100] = runTime(f,100,x0,Tol,-100,100);
BisectionTime_100 = mean(time_B_100)
fsolveTime_100 = mean(time_f_100)
%% 
% *Functions*
% 
% 2.1   function g(ne,Nbar,A,alpha,epsilon,sigma,psi)

function [g] = RHSequ(ne,Nbar,A,alpha,epsilon,sigma,psi)
    g = Nbar-(psi/((1-alpha)*A.^(1-sigma))*ne.^(alpha+sigma*(1-alpha))).^(1/epsilon);
end

%% 
% 2.2   Function Iteration Method

function [x1] = FunIterMethod(f,x0,Tol)
    x1 = f(x0);
    dst = norm(x1-x0);
    cnt = 1;
    while dst>Tol && cnt<1000
        x0 = x1;
        x1 = f(x0);
        dst = norm(x1-x0);
        cnt = cnt + 1;
    end
end

%% 
% 3   Bisection

function [x] = BisectionMethod(f,a,b,Tol)
    if sign(f(a)) == sign(f(b))
        error('sign of f(a) == sign of f(b)');
    end
    dst = b-a; 
    cnt = 0; 
    while dst>Tol && cnt<100
        x = 0.5*(a+b); 
        if sign(f(x))==sign(f(a))
            a = x; 
        else 
            b = x; 
        end
        dst = b-a; 
        cnt = cnt + 1; 
    end
end

%% 
% 6   Runtime function

function [time_B,time_f] = runTime(f,n,x0,Tol,a,b)
    time_B = zeros(1,n);
    time_f = zeros(1,n);
    for i = 1:n
        tic
        BisectionMethod(f,a,b,Tol);
        time_B(i) = toc;
        tic
        fsolve(f,x0);
        time_f(i) = toc;

    end
end