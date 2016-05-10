#include <iostream>
#include <string>
#include <vector>



#include "Vende++.h"
#include "Menus.h"
#include "utils.h"


int main(){
  string loja, fichClients, fichProdutos, fichTransacoes;
  ifstream fclients, fproducts, ftransactions;
  string line;
  //Clientes
  cout << "Nome do ficheiro de clientes? ";
  cin >> fichClients;
  checkFile(fclients, fichClients);
  //lineClients

  //Ficheiro de produtos
  cout << "Name of the products' file? ";
  cin >> productsFile;
  fproducts.open(productsFile);
  while (!fproducts.is_open())
  {
	  cout << "The file " << "\"" << productsFile << "\"" << " couldn't be found." << endl << endl;
	  cout << "Insert the products' file name again: ";
	  cin >> productsFile;
	  fproducts.open(productsFile);
  }
  cout << "The file was sucessfully read.";
  cout << endl;
  while (getline(fproducts, line))
  {
	  string product = line;
	  products.push_back(product);
  }
  //
  cout << endl;
  //

  //Ficheiro de transacoes
  cout << "Name of the transactions' file? ";
  cin >> transactionsFile;
  ftransactions.open(transactionsFile);
  while (!ftransactions.is_open())
  {
	  cout << "The file " << "\"" << transactionsFile << "\"" << " couldn't be found." << endl << endl;
	  cout << "Insert the transactions' file name again: ";
	  cin >> transactionsFile;
	  ftransactions.open(transactionsFile);
  }
  cout << "The file was sucessfully read.";
  cout << endl;
  while (getline(ftransactions, line))
  {
	  int index = line.find_first_of(';');
	  int index2 = line.find_last_of(';');
	  string id = line.substr(0, index - 1);
	  string date = line.substr(index + 2, (index2 - 1) - (index + 2));
	  string list = line.substr(index2 + 2);
	  Transactions_t t;
	  t.id = stoi(id);
	  t.date = date;
	  t.productslist = list;
	  transactions.push_back(t);
  }

  //
  cout << endl;
  //
  // pede a informacoo sobre o nome da loja e os 3 ficheiros com
  // informacoo de clientes, produtos e transacoes
  if(! infoInicial(loja, fichClients, fichProdutos, fichTransacoes))
    return(-1);

  // cria uma loja
  VendeMaisMais supermercado(loja, fichClients, fichProdutos, fichTransacoes);

  cout << "Informacao da loja '" << loja << " do supermercado Vende++:" << endl;
  cout << supermercado << endl;  // mostra estatisticas da loja

  opcoesIniciais(supermercado); // menu inicial com as grandes opcoes
				// que implementam as funcioanlidades
				// disonibilizadas

  return 0;
}
