/*
 * Sum.cpp
 */

#include "Sum.h"
#include <chrono>
#include <iostream>

string calcSum(int* sequence, int size)
{
    int min[size+1];
    int ind[size+1];

    fill_n(min, size+1, 0);
    fill_n(ind, size+1, 0);

    for(int m=1;m<=size;m++){
        int k=0;
        while(k<=size-m) {
            int sum=0;
            for (int i = k; i < k+m; i++) {
                sum += sequence[i];
            }
            if (min[m - 1] == 0 || min[m - 1] > sum) {
                min[m - 1] = sum;
                ind[m - 1] = k;
            }
            k++;
        }
    }
    string output="";

    for (int i=0;i<size;i++){
        output+=to_string(min[i])+',';
        output+=to_string(ind[i])+';';
    }
	return output;
}

