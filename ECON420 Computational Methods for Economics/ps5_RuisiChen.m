clear;clc
% README: functions are at the end of this document
%% 
% *Q1    5.1*

q1 = @(p) 2*p.^(-0.5)
a=1, b=4, n=10001
%% 
% (b) trapezoid rule

DeltaConsumerSurplus_T = NewtonCotes_T(q1,a,b,n)
%% 
% (c) Simpson rule

DeltaConsumerSurplus_S = NewtonCotes_S(q1,a,b,n)
%% 
% (d) Gauss-Legendre rule

% function in CompEcon
[P_1d,W_1d] = qnwlege(n,a,b);
DeltaConsumerSurplus_G = W_1d'*q1(P_1d)
%% 
% (e) equidistributed sequence rule

% function in CompEcon
[P_1e,W_1e]=qnwequi(n,a,b);
DeltaConsumerSurplus_Q = ((b-a)/n)*sum(q1(P_1e))
%% 
% *Q2    5.2*

f2 = @(alpha, lamda) exp(alpha.*lamda-lamda.^2/2);
g = NewtonCotes_S2(f2,0,100,1000);
h = @(alpha) alpha*g(alpha)-1;
alpha = fsolve(h,0)
%% 
% *Q3    5.5*

% p_bar = 0;
% p_bar = 1;
p_bar = 2; 
%% 
% (b)

% find the p and f as function of y
syms ef y p
p3 = @(y,ef) solve(y.*(1+(ef).^0.5)-p.^(-0.2)-p.^(-0.5) == 0,p, 'Real', true)
f3 = @(y,ef) max(p_bar,p3(y,ef))

[y_tilde,W3] = qnwlogn(100,0,0.03);
Equ = @(ef) W3'.*f3(y_tilde,ef) - ef;
Ef = fsolve(Equ,0.5)
%% 
% (c)

FunVar3c = @(y) (f3(y,Ef)-Ef).^2
Varf = w'*FunVar3c(y_tilde)
%% 
% (d)

a = 1 + Ef^0.5;
q3 = @(y) a*y;
FunEfq = @(y) f3(y,Ef).*q3(y)
Efq = w'*FunEfq(y_tilde)
%% 
% (e)

FunVar3e = @(y) (f3(y,Ef).*q3(y)-Efq).^2
Varfq = w'*FunVar3e(y_tilde)
%% 
% (a)

FunEa = @(y) q(y).*(f(y,Ef)-p(y,Ef))
Ea = w'*FunEa(y_tilde)
%% 
% *Functions*
% 
% 5.1

function [INT]=NewtonCotes_T(f,a,b,n)
    h=(b-a)/(n-1);
    w=ones(n,1)*h;
    w(1,1)=h/2;
    w(n,1)=h/2;
    xi=linspace(a,b,n)';
    INT=w'*f(xi);
end

function [INT]=NewtonCotes_S(f,a,b,n)
    x=linspace(a,b,n)';
    h=(b-a)/(n-1);
    w=ones(1,n);
    w(1,1)=h/3;
    w(1,n)=h/3;
    for i=2:n-1
        if rem(i,2)==0
            w(1,i)=4*h/3;
        else
            w(1,i)=2*h/3;
        end
    end
    INT=w*f(x);
end

%% 
% 5.2

function [INT]=NewtonCotes_S2(f,a,b,n)
    x=linspace(a,b,n)';
    h=(b-a)/(n-1);
    w=ones(1,n);
    w(1,1)=h/3;
    w(1,n)=h/3;
    for i=2:n-1
        if rem(i,2)==0
            w(1,i)=4*h/3;
        else
            w(1,i)=2*h/3;
        end
    end
    INT=@(alpha) w*f(alpha,x);
end
%% 
% 5.5