/*
 * Change.cpp
 */

#include "Change.h"

string calcChange(int m, int numCoins, int *coinValues)
{
    if (m == 0)
        return "";

    int minCoins[m+1];
    int lastCoin[m+1];

    fill_n(minCoins, m+1, 0);
    fill_n(lastCoin, m+1, 0);
    //coinValues ordenados
    for(int i=1;i<=numCoins;i++){ //numero de moedas
        for (int k=coinValues[i-1];k<=m;k++){ //montante
            if (minCoins[k] == 0 || minCoins[k-coinValues[i-1]]+1 < minCoins[k]){
                minCoins[k]=minCoins[k-coinValues[i-1]]+1;
                lastCoin[k]=coinValues[i-1];
            }
        }
    }
    string output = "";

    if (minCoins[m] == 0)
        return "-";

    for (int k = m; k>0; k-=lastCoin[k]) {
        output += to_string(lastCoin[k]) + ";";
    }

    return output;
}


