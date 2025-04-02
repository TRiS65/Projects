clear;clc
% README: functions are at the end of this document
%%
N = 10000;
alpha = rand(N,1);
sigma = rand(N,1);
x  = rand(N,1);
p = rand(N,1);
%% 
% 1(b)

y_b = VecOpr(N,alpha,sigma,x,p)
%% 
% 1(c)

y_c = mean(p.*alpha.*(x.^sigma))
%% 
% 1(d)

tic
y_b = VecOpr(N,alpha,sigma,x,p);
time_b = toc
tic
y_c = mean(p.*alpha.*(x.^sigma));
time_c = toc

if time_b > time_c
    disp('for loop is faster')
else 
    if time_b < time_c
        disp('vector operation is faster')
    else
        disp('no difference')
    end
end
%%
function y=VecOpr(N,alpha,sigma,x,p)
    sum = 0;
    for i = 1:N
        sum = sum + p(i)*alpha(i)*x(i)^sigma(i);
    end
    y = sum/N;
end