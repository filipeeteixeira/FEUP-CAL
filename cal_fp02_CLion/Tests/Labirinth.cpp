/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
#include <unistd.h>
using namespace std;



Labirinth::Labirinth(int values[10][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			labirinth[i][j] = values[i][j];
}


void Labirinth::initializeVisited()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			visited[i][j] = false;
}



void  Labirinth::printLabirinth(bool visited[][10])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++) {
            if (visited[i][j])
                cout << 'X' << " ";
            else
                cout << labirinth[i][j] << " ";
        }
		cout << endl;
	}
    cout << endl;
}


bool Labirinth::findGoal(int x, int y)
{
    if (first) {
        initializeVisited();
        first=false;
    }

    if(labirinth[x][y]==2)
        return true;

    if(labirinth[x][y+1]!=0 and !visited[x][y + 1]){
        visited[x][y + 1]=true;

        if (findGoal(x,y+1))
            return true;
    }
    if(labirinth[x][y-1]!=0 and !visited[x][y - 1]){
        visited[x][y - 1]=true;

        if (findGoal(x,y-1))
            return true;
    }
    if(labirinth[x+1][y]!=0 and !visited[x+1][y]){
        visited[x+1][y]=true;

        if (findGoal(x+1,y))
            return true;
    }
    if(labirinth[x-1][y]!=0 and !visited[x-1][y]){
        visited[x-1][y]=true;

        if (findGoal(x-1,y))
            return true;
    }
	return false;
}


