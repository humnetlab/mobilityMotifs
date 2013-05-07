function P=_prob(n,k,p1,p2)

% returns P_n_k - prob. of k successes out of n slots

sizeM = 2*(n+1);

U = zeros(sizeM,1);


U(2*k+1)=1; % ones at place of states with k successes 
U(2*k+1+1)=1;%

% to account for redundancy. this implementation contains redundant 
% (non-existent) states (the second and one before the last) for the 
% sake of consistent indexing

U(2)=0;
U(2*(n+1)-1)=0;

%initial conditions (0,0)
xi0 = zeros(1,sizeM);
xi0(1) = 1;


M=zeros(sizeM,sizeM,n);


for i=1:n
    A=tprob(n,p1,p2);
   
    M(:,:,i)=A;
end

% product = zeros(sizeM);
product = eye(sizeM);
for i=1:n
    product =  product * M(:,:,i);
end

P = xi0*product*U;
disp(P)


function A=tprob(n,p1,p2)

% constructs the transition matrix for Markov chain embedding
% of the problem of the number of successes (out of home locations)

% n - number of time intervals per day (e.g. 32 half hour intervals)


SizeA = 2*(n+1);
A = zeros(SizeA);

% odd indexes correspond to zero (home)
% even indexes correspond to ones (away)

for i=0:n-1 
    % A(n,0) is impossible (redundant state). A(n,1) is absorbing state.
    
    A(2*i+1,2*i+1) =  1 - p1; % H -> H
    if i < (n-1) % there could not be (n-1,0) -> (n,1)
        A(2*i+1,2*(i+1)+1+1) = p1; % H -> A
    end
    if i>0 && i<n % (0,1) is impossible
        A(2*i+1+1,2*i+1) = 1 - p2; % A -> H
        A(2*i+1+1,2*(i+1)+1+1) = p2; % A -> A
    end
    
end

% absorbing states have a higher priority, than above transition rules

A(2*(n-1)+1,2*(n-1)+1) = 1;
A(2*n+1+1,2*n+1+1) = 1;
