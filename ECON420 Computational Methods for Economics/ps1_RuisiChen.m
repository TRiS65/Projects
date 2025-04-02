clear, clc
%% Problem 1. Matrix operations

% 1(a)
A = [2,5,4,1; 3,6,1,2; 1,3,8,9];

% 1(b)
v = A(3,:);

% 1(c)
B = A.^2;

% 1(d)
A(A>5) = 0; % meaning: Replace all the elements that greater than 5 in A by zero.


%% Problem 2. Loops - while

i = 1;
while i <= 5
    disp(i*5)
    i = i + 1;
end 

%% Problem 3. Loops - For

for j = 5:5:25
    disp(j)
end


%% Problem 4 Functions and matrices

function y = tellsign(x)
    if x > 0
        y = 'Positive';
    else
        if x == 0
            y = 'Zero';
        else 
            y = 'Negative';
        end
    end
end

% 4(a) modify tellsign into matrix format

function T = MatrixSign(S)
    r = size(S,1);
    c = size(S,2);
    T = strings([r,c]);
    for i = 1:r
        for j = 1:c
            T(i,j) = tellsign(S(i,j));
        end 
    end
end


%% Problem 5 Nesting

function f = SumLower10(v)
    if v(1,1) ~= 1
        error('v(1,1) is not 1');
    end 
    f = 0;
    r = size(v,1);
    c = size(v,2);
    for i = 1:r
        for j = 1:c 
            if v(i,j) <= 10
                f = f + v(i,j);
            end
        end 
    end
end