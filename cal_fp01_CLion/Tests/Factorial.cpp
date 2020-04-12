/*
 * Factorial.cpp
 */

#include "Factorial.h"
#include <vector>

int factorialRecurs(int n)
{
    if (n==1 || n==0) {
        return n;
    }
    else{
        return n*factorialRecurs(n-1);
    }
}

int factorialDinam(int n)
{
    /*
    int fact=n;
	for (int i=1; i<n;i++){
	    fact=fact*i;
	}
	return fact;
    */
    int v[n+1];

    fill_n(v,n+1,1);

    for(int i=1;i<=n;i++){
        v[i]=i*v[i-1];
    }
    return v[n];
}
