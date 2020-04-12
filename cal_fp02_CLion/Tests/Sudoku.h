/*
 * Sudoku.h
 *
 */

#ifndef SUDOKU_H_
#define SUDOKU_H_

#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <ctime>

using namespace std;

#define IllegalArgumentException -1

class Sudoku
{
	/**
	 * numbers[i][j] - n�mero que ocupa a linha i, coluna j (de 0 a 8)
	 * 0 quer dizer n�o preenchido.
	 */
	int numbers[9][9];



	/**
	 * Informa��o derivada da anterior, para acelerar processamento (n�mero de 1 a 9, nao usa 0)
	 */
	int countFilled;
	bool columnHasNumber[9][10];
	bool lineHasNumber[9][10];
	bool block3x3HasNumber[3][3][10];

	void initialize();

public:
    int solutions=0;
	/** Inicia um Sudoku vazio.
	 */
	Sudoku();

	/**
	 * Inicia um Sudoku com um conteudo inicial.
	 * Lan�a excepcao IllegalArgumentException se os valores
	 * estiverem fora da gama de 1 a 9 ou se existirem n�meros repetidos
	 * por linha, coluna ou bloc 3x3.
	 *
	 * @param nums matriz com os valores iniciais (0 significa por preencher)
	 */
	Sudoku(int nums[9][9]);

	/**
	 * Obtem o conteudo actual (sa para leitura!).
	 */
	int** getNumbers();


	/**
	 * Verifica se o Sudoku ja esta completamente resolvido
	 */
	bool isComplete();


	/**
	 * Resolve o Sudoku.
	 * Retorna indicao de sucesso ou insucesso (sudoku impossivel).
	 */
	bool solve();


	/**
	 * Imprime o Sudoku.
	 */
	void print();

    /**
     * Resolve o Sudoku.
     * Retorna 1 se apenas uma solucao, 2 se duas ou mais solucoes. 0 se impossivel
     */
	bool multiplicity();

    void makeSudoku();
};



#endif /* SUDOKU_H_ */
