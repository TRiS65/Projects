clear;clc
% README: functions are at the end of this document

%% Problem 1

A = [54 14 -11 2; 14 50 -4 29; -11 -4 55 22; 2 29 22 95];
b = ones(4,1);

% a. L-U decomposition
x_LU = A\b

x0 = rand(4,1); % randomly pick an initial x

% b. Gauss-Jacobi iteration
[x_GJ,countJ] = solveGaussJacobi(A,b,x0)

% c. Gauss-Seidel iteration
[x_GS,countS] = solveGaussSeidel(A,b,x0)

% Compare
diffJ = x_LU-x_GJ
diffS = x_LU-x_GS
diff = countJ-countS
% The answer through Gauss-Jacobi and Gauss-Seidel are similar to L-U decomposition, only has small differences. 
% Thus, we could say that the answers are agree with the L-U decomposition solution. 
% In addition, Jacobi needs more iterations to get the answer. 


%% Problem 2

A = rand(100,100);
b = rand(100,1);

[time_a,time_b,time_c] = runTime(A,b,50);
% sum of the first n elements in vector is the answer

% a. x=A\b
a_1 = time_a(1)
a_10 = sum(time_a(1:10))
a_50 = sum(time_a(1:50))

% b. x=U\(L\b)
b_1 = time_b(1)
b_10 = sum(time_b(1:10))
b_50 = sum(time_b(1:50))

% a. x=A^(-1)b
c_1 = time_c(1)
c_10 = sum(time_c(1:10))
c_50 = sum(time_c(1:50))


%% Problem 3

% a
% see the pdf

% b
% see the pdf

% c
% loading data
Table = load('ps3_data.mat');
n = length(Table.q)

[alpha_0,alpha_1] = OLS([ones(n,1) Table.elecp],Table.q)

[beta_0,beta_1] = OLS([ones(n,1) Table.elecp],Table.pcars)

DemandElasiticity = alpha_1/beta_1

% d
% see the pdf


%% Functions

% Problem 1
function [x,i] = solveGaussJacobi(A,b,x0)
    Q = diag(diag(A));
    I = eye(width(A));
    i = 1;
    prev = x0;
    curr = inv(Q)*b + (I-inv(Q)*A)*prev;
    while (norm(curr-prev)>0.00001 && i<=100)
        %display(norm(curr-prev))
        prev = curr;
        curr = inv(Q)*b+(I-inv(Q)*A)*prev;
        i = i+1;
    end
    x = curr;
end

function [x,i] = solveGaussSeidel(A,b,x0)
    Q = triu(A);
    I = eye(width(A));
    i = 1;
    prev = x0;
    curr = inv(Q)*b + (I-inv(Q)*A)*prev;
    while (norm(curr-prev)>0.00001 && i<=100)
        %display(norm(curr-prev))
        prev = curr;
        curr = inv(Q)*b+(I-inv(Q)*A)*prev;
        i = i+1;
    end
    x = curr;
end


% Problem 2
% store each runtime into the array
function [time_a,time_b,time_c] = runTime(A,b,n)
    time_a = zeros(1,n);
    time_b = zeros(1,n);
    time_c = zeros(1,n);
    [L,U] = lu(A);
    A_inv = inv(A);
    for i = 1:n
        tic
        x = A\b;
        time_a(i) = toc;
        tic
        x = U\(L\b);
        time_b(i) = toc;
        tic
        x = A_inv*b;
        time_c(i) = toc;
    end
end

% Problem 3
% a is alpha_0, b is alpha_1
function [a,b] = OLS(X,Y)
    parameter = (X'*X)\(X'*Y);
    a = parameter(1);
    b = parameter(2);
end