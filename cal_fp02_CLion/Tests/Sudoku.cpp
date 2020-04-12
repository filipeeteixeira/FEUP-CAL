/*
 * Sudoku.cpp
 *
 */

#include "Sudoku.h"
#include <unistd.h>

/** Inicia um Sudoku vazio.
 */
Sudoku::Sudoku()
{
	this->initialize();
}

/**
 * Inicia um Sudoku com um conte�do inicial.
 * Lan�a excep��o IllegalArgumentException se os valores
 * estiverem fora da gama de 1 a 9 ou se existirem n�meros repetidos
 * por linha, coluna ou bloc 3x3.
 *
 * @param nums matriz com os valores iniciais (0 significa por preencher)
 */
Sudoku::Sudoku(int nums[9][9])
{
	this->initialize();

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (nums[i][j] != 0)
			{
				int n = nums[i][j];
				numbers[i][j] = n;
				lineHasNumber[i][n] = true;
				columnHasNumber[j][n] = true;
				block3x3HasNumber[i / 3][j / 3][n] = true;
				countFilled++;
			}
		}
	}
}

void Sudoku::initialize()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int n = 0; n < 10; n++)
			{
				numbers[i][j] = 0;
				lineHasNumber[i][n] = false;
				columnHasNumber[j][n] = false;
				block3x3HasNumber[i / 3][j / 3][n] = false;
			}
		}
	}

	this->countFilled = 0;
}

/**
 * Obtem o conte�do actual (s� para leitura!).
 */
int** Sudoku::getNumbers()
{
	int** ret = new int*[9];

	for (int i = 0; i < 9; i++)
	{
		ret[i] = new int[9];

		for (int a = 0; a < 9; a++)
			ret[i][a] = numbers[i][a];
	}

	return ret;
}

/**
 * Verifica se o Sudoku j� est� completamente resolvido
 */
bool Sudoku::isComplete()
{
	return countFilled == 9 * 9;
}



/**
 * Resolve o Sudoku.
 * Retorna indicacao de sucesso ou insucesso (sudoku impossivel).
 */
bool Sudoku::solve()
{
    if (isComplete()) return true;

    bool found=false;
    int i1, i2;
    for(int i=1;i<10;i++){
        for (i1=0;i1<9;i1++){
            for (i2=0;i2<9;i2++){
                int counter=0;
                if(numbers[i1][i2]==0){
                    for(int j=1;j<10;j++){
                        if (block3x3HasNumber[i1/3][i2/3][j] or lineHasNumber[i1][j] or columnHasNumber[i2][j]){
                            counter++;
                        }
                    }
                    if (9-counter==i){
                        found=true;
                        break;
                    }
                }
            }
            if(found) break;
        }
        if(found) break;
    }
    if(!found)
        return false;

    for(int j=1;j<10;j++){
        if (!block3x3HasNumber[i1/3][i2/3][j] and !lineHasNumber[i1][j] and !columnHasNumber[i2][j]){
            numbers[i1][i2]=j;

            countFilled++;
            block3x3HasNumber[i1/3][i2/3][j]=true;
            lineHasNumber[i1][j]=true;
            columnHasNumber[i2][j]=true;

            if (solve()) return true;
            numbers[i1][i2]=0;
            countFilled--;
            block3x3HasNumber[i1/3][i2/3][j]=false;
            lineHasNumber[i1][j]=false;
            columnHasNumber[i2][j]=false;
        }
    }
	return false;
}

bool Sudoku::multiplicity(){

    if (solutions>=1) //retorna true quando há mais do que 1 solução
        return true;

    if (isComplete()){
        this->solutions++;
        return true;
    }

    bool found=false;
    int i1, i2;
    for(int i=1;i<10;i++){
        for (i1=0;i1<9;i1++){
            for (i2=0;i2<9;i2++){
                int counter=0;
                if(numbers[i1][i2]==0){
                    for(int j=1;j<10;j++){
                        if (block3x3HasNumber[i1/3][i2/3][j] or lineHasNumber[i1][j] or columnHasNumber[i2][j]){
                            counter++;
                        }
                    }
                    if (9-counter==i){
                        found=true;
                        break;
                    }
                }
            }
            if(found) break;
        }
        if(found) break;
    }
    if(!found)
        return false;

    for(int j=1;j<10;j++){
        if (!block3x3HasNumber[i1/3][i2/3][j] and !lineHasNumber[i1][j] and !columnHasNumber[i2][j]){
            numbers[i1][i2]=j;

            countFilled++;
            block3x3HasNumber[i1/3][i2/3][j]=true;
            lineHasNumber[i1][j]=true;
            columnHasNumber[i2][j]=true;

            multiplicity();

            numbers[i1][i2]=0;
            countFilled--;
            block3x3HasNumber[i1/3][i2/3][j]=false;
            lineHasNumber[i1][j]=false;
            columnHasNumber[i2][j]=false;

        }
    }
    return false;
}



/**
 * Imprime o Sudoku.
 */
void Sudoku::print()
{
	for (int i = 0; i < 9; i++)
	{
		for (int a = 0; a < 9; a++)
			cout << this->numbers[i][a] << " ";

		cout << endl;
	}
	cout << endl;
}


void Sudoku::makeSudoku(){ //not working properly i guess
    int randline, randcol, randnum;
    do {
        std::srand(std::time(nullptr));
        randline = rand() % (8 - 0 + 1) + 0;
        randcol = rand() % (8 - 0 + 1) + 0;
        randnum = rand() % (9 - 1 + 1) + 1;
    }while(numbers[randline][randcol]!=0 or block3x3HasNumber[randline/3][randcol/3][randnum] or columnHasNumber[randcol][randnum] or lineHasNumber[randline][randnum]);

    numbers[randline][randcol]=randnum;
    countFilled++;
    block3x3HasNumber[randline/3][randcol/3][randnum]=true;
    lineHasNumber[randline][randnum]=true;
    columnHasNumber[randcol][randnum]=true;

    if (countFilled>8) {
        print();
        sleep(2);
        this->solutions = 0;
        multiplicity();
        cout << solutions << endl;
        if (solutions > 1) {
            makeSudoku();
        } else if (solutions == 1) {
            return;
        } else if (solutions == 0) {
            numbers[randline][randcol] = 0;
            countFilled--;
            block3x3HasNumber[randline / 3][randcol / 3][randnum] = false;
            lineHasNumber[randline][randnum] = false;
            columnHasNumber[randcol][randnum] = false;
            makeSudoku();
        }
    }
    else{
        makeSudoku();
    }
}