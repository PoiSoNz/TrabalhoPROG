#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>
#include "Cliente.h"
#include "Data.h"
#include "Produto.h"
#include "Transacao.h"
#include <map>
//#include "Vende++.h"

#include "defs.h"

using namespace std;


void clearScreen();

unsigned short int leUnsignedShortInt(unsigned short int min, unsigned short int max);

int leInteiro(int min, int max);

void checkFile(ifstream &stream, string nomeFicheiro);

void extractProducts(vector<string> &vetor, string listaprodutos, unsigned int counter, unsigned int numVirgulas);//extrai para o vetor de produtos(private a esta classe) cada produto duma lista de produtos

void trim(string &s);//comenta isto sff

int encontraPosicao(string s, char *c, unsigned int num);// retorna a posição do numº caracter *c na string s

bool clienteMontante(const Cliente c1, const Cliente c2);//retorna true se o volume de compras de c1 < c2. Esta funcao ira servir para usar em sorts (ordem crescent de montantes)
bool clienteMontanteInvertido(const Cliente c1, const Cliente c2);// retorna false se o volume de compras de c1 < c2.Esta funcao ira servir para usar em sorts (ordem decrescente de montantes)

bool transacaoCrono(const Transacao t1, const Transacao t2);//devolve true caso a data da transacao t1 for anterior ou igual a t2 e false caso contrario. Esta funcao ira servir para usar em sorts (ordem cronologica)

bool verifyDate(int day, int month, int year);//verifica se uma data e valida, devolvendo true caso seja ou false caso contrario

bool verifyDatesOrder(int oldDay, int oldMonth, int oldYear, int recentDay, int recentMonth, int recentYear); //Verifica se duas datas se encontram na ordem certa. A data oldDay/oldMonth/oldYear tem de ser anterior à data recentDay/recentMonth/recentYear

bool verifyProduct(string nome,const vector<Produto> &vec);//verifica se um nome de um produto esta num vetor de produtos
bool verifyProduct(string nome, const vector<string> &vec);//verifica se um nome de um produto esta num vetor de strings

bool checkProduct(unsigned int clientId, string product, const vector<Transacao>&transactionsVector);

int clientVectorPosition(unsigned int id, const vector<Cliente> &clientsVector);//recebe o ID do cliente e retorna a posicao dele no vetor de clientes
int clientVectorPosition(string nome, const vector<Cliente> &clientsVector);//recebe o NOME do cliente e retorna a posicao dele no vetor de clientes

int productVectorPosition(string nome, const vector<Produto> &productsVector);

string mostFrequentName(const vector<string> &vec);

float precoProduto(string produto, const vector<Produto> &vec);

Data IntroduzaData();//pede uma data (por partes) e verifica se e valida. Devolve um objecto do tipo Data de acordo com os valores introduzidos
