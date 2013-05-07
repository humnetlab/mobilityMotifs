#!/usr/bin/python

""" returns the probability P to visit k locations given n time slots available
"""


import sys
# sys.path.append("/Library/Python/2.6/site-packages/")
import numpy


def run_prob(n=0, k=0, p1=0.0, p2=0.0):    

    sizeM = 2 * (n + 1)

    U = numpy.zeros((sizeM, 1))

    U[2 * k ] = 1 # (k,0)
    U[2 * k + 1 ] = 1# (k,1)


    U[1] = 0 # (0,1) does not exist
    U[2 * n]= 0 # (n,0) does not exist (because we always start at home) 

    # initial conditions
    xi0 = numpy.zeros((1, sizeM))
    xi0[0,0] = 1 # we start at home; note the indexing of a row vector
    

    M = numpy.zeros((sizeM, sizeM, n))
    A = tprob(n, p1, p2) # calculate one-step transition matrix
    product = A
    for i in range(n-1): #until n-2
    
        product = numpy.dot(product,A)
    
    
    P = numpy.dot(xi0,numpy.dot(product,U))
    
    return A,P,U,xi0,product


def tprob(n= 0, p1= 0.0, p2= 0.0):
    """ returns matrix A """
    
    SizeA = 2 * (n + 1)
    A = numpy.zeros((SizeA,SizeA))
    
    #  A[0,1] and A[n,0] are impossible (redundant states).
    
    for i in range(n): # until n-1


        A[2 * i , 2 * i] = 1 - p1    # H -> H
        if i < (n - 1):        # there could not be (n-1,0) -> (n-1,1)
            A[2 * i, 2 * (i+1) + 1] = p1        # H -> A
        
        if i > 0 and i < n:        # (0,1) is impossible
            A[2 * i + 1, 2 * i ]= 1 - p2        # A -> H
            A[2 * i + 1 , 2 * (i+1) + 1 ] = p2        # A -> A

    # absorbing states have a higher priority, than above transition rules
    A[2 * (n - 1) , 2 * (n - 1)] = 1 # (n-1,0) -> (n-1,0)
    A[2 * n + 1, 2 * n + 1] = 1 # (n,1) -> (n,1)
    
    return A
    
    
if __name__=="__main__":
    
    
    n = int(sys.argv[1])
    k = int(sys.argv[2])
    p1 = float(sys.argv[3])
    p2 = float(sys.argv[4])
    
    A,P,U,xi0,product = run_prob(n, k, p1, p2)
#    s= "p1 = %.5f and p2 = %.5f" % (p1,p2)
#    print s
    s = "P_k=%d_n=%d = %.10f" % (k,n,P)
    print s
