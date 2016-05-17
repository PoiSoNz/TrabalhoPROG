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

void trim(string &s);//elimina qualquer espaço no início e no fim de uma string, e quaisquer dois ou mais espaços entre duas palavras de uma mesma string são reduzidos a apenas um espaço

int encontraPosicao(string s, char *c, unsigned int num);// retorna a posição do numº caracter *c na string s

bool verifyDatesOrder(int oldDay, int oldMonth, int oldYear, int recentDay, int recentMonth, int recentYear); //Verifica se duas datas se encontram na ordem certa. A data oldDay/oldMonth/oldYear tem de ser anterior à data recentDay/recentMonth/recentYear
