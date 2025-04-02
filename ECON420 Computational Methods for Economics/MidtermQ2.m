clear;clc
% README: functions (2b,2e) are at the end of this document
% Other part of the Questions: see the pdf
%% 
% 2(c)

W = 1;
alpha = 0.66;
v = 1.3
sigma = 2;
psi = 1.5;
beta = 0.98;
r = 0.04;

f = @(l) F(l,W,alpha,sigma,v,psi,beta,r);
f_w0 = @(l) F(l,0,alpha,sigma,v,psi,beta,r);
f_w2 = @(l) F(l,2,alpha,sigma,v,psi,beta,r);

L = linspace(0.1,1.5,100);
plot(L,f(L),L,f_w0(L),L,f_w2(L))
legend(["f:w=1","f:w=0","f:w=2"])
legend("Position", [0.63242,0.14717,0.22266,0.2])

%% 
% 2(f)

W = 2

l1 = 0.5
ls_1 = LaborSupply(l1,W,alpha,sigma,v,psi,beta,r)

l2 = 3
ls_2 = LaborSupply(l2,W,alpha,sigma,v,psi,beta,r)

%% 
% *Functions*
% 
% 2(b)

function [LHS] = F(l,W,alpha,sigma,v,psi,beta,r)
    LHS = l.^(1-alpha) + W - (1./(l.^((v+alpha)/sigma))) * ((1-alpha)/psi)^(1/sigma) * (1+(beta*(1+r))^(1/sigma)/(1+r));
end
%% 
% 2(e)

% f is the derivative of F
function [f] = Function_f(l,alpha,sigma,v,psi,beta,r)
    f = (1-alpha)/(l.^(alpha)) + (v+alpha)/sigma * ((1-alpha)/psi).^(1/sigma) * (1+((beta*(1+r)).^(1/sigma))/(1+r))/(l.^(1+(v+alpha)/sigma));
end

function [ls] = LaborSupply(l0,W,alpha,sigma,v,psi,beta,r)
    MaxIt = 1000;
    Tol = 1e-6;

    % g is the derivative of G
    G = @(l) F(l,W,alpha,sigma,v,psi,beta,r);
    g = @(l) Function_f(l,alpha,sigma,v,psi,beta,r);

    ls = l0-G(l0)/g(l0);
    cnt = 1;
    while norm(G(ls))>Tol && cnt<MaxIt
        ls = ls-G(ls)/g(ls);
        cnt = cnt+1;
    end
end