#include <iostream>
#include <string>
#include <vector>



#include "Vende++.h"
#include "Menus.h"
#include "utils.h"


int main(){
  string loja, fichClients, fichProducts, fichTransactions;
  ifstream fclients, fproducts, ftransactions;
  
  //Nome da loja
  cout << "Qual o nome da loja? ";
  getline(cin, loja);
  cout << endl;

  //Clientes
  cout << "Nome do ficheiro de clientes? ";
  cin >> fichClients;
  checkFile(fclients, fichClients);

  //Produtos
  cout << "Nome do ficheiro de produtos? ";
  cin >> fichProducts;
  checkFile(fproducts, fichProducts);

  //Ficheiro de transacoes
  cout << "Nome do ficheiro de transacoes? ";
  cin >> fichTransactions;
  checkFile(ftransactions, fichTransactions);

  //
  VendeMaisMais obj = VendeMaisMais(loja, fichClients, fichProducts, fichTransactions);
  obj.fillClientsVector(fclients);
  obj.fillProductsVector(fproducts);
  obj.fillTransactionsVector(ftransactions);

  // pede a informacoo sobre o nome da loja e os 3 ficheiros com
  // informacoo de clientes, produtos e transacoes
  if(!infoInicial(loja, fichClients, fichProducts, fichTransactions))
    return(-1);

  // cria uma loja
  VendeMaisMais supermercado(loja, fichClients, fichProducts, fichTransactions);

  cout << "Informacao da loja '" << loja << " do supermercado Vende++:" << endl;
  cout << supermercado << endl;  // mostra estatisticas da loja

  opcoesIniciais(supermercado); // menu inicial com as grandes opcoes
				// que implementam as funcioanlidades
				// disonibilizadas

  return 0;
}
