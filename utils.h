#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>
//#include "Cliente.h"
//#include "Data.h"
//#include "Produto.h"
//#include "Vende++.h"//ver se estes sao necessarios

#include "defs.h"

using namespace std;


void clearScreen();

unsigned short int leUnsignedShortInt(unsigned short int min, unsigned short int max);

int leInteiro(int min, int max);

void checkFile(ifstream &stream, string nomeFicheiro);

void extractProducts(vector<string> vetor, string listaprodutos);//extrai para o vetor de produtos(private a esta classe) cada produto duma lista de produtos

void lowerCase(string &s);//converte cada caracter de uma string de C++ para minuscula

void trim(string &s);//comenta isto sff

int encontraPosicao(string s, char *c, unsigned int num);// retorna a posição do numº caracter *c na string s
