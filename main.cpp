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
  trim(loja);
  cout << endl;

  //Clientes
  cout << "Nome do ficheiro de clientes? ";
  cin >> fichClients;
  checkFile(fclients, fichClients);

  //Produtos
  cout << "Nome do ficheiro de produtos? ";
  cin >> fichProducts;
  checkFile(fproducts, fichProducts);

  //Transacoes
  cout << "Nome do ficheiro de transacoes? ";
  cin >> fichTransactions;
  checkFile(ftransactions, fichTransactions);

  //Loja
  //cria uma loja e preenche os vetores
  VendeMaisMais supermercado = VendeMaisMais(loja, fichClients, fichProducts, fichTransactions);
  supermercado.fillClientsVector(fclients);
  supermercado.fillProductsVector(fproducts);
  //supermercado.fillTransactionsVector(ftransactions);

  if(!infoInicial(loja, fichClients, fichProducts, fichTransactions))//nao se se isto vai ficar
    return(-1);

  cout << "Informacao da loja '" << loja << " do supermercado Vende++:" << endl;
  cout << supermercado << endl;  // mostra estatisticas da loja

  opcoesIniciais(supermercado); // menu inicial com as grandes opcoes
				// que implementam as funcioanlidades
				// disonibilizadas

  return 0;
}
