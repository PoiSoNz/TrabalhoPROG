#pragma once

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include<algorithm>


#include "defs.h"
#include "Data.h"
#include "Cliente.h"
#include "Transacao.h"
#include "Produto.h"
#include "utils.h"


using namespace std;

class VendeMaisMais{
	//friend void fillClientsVector(ifstream &stream, vector<Cliente> &vec);//preenche o vetor de clientes
 private:
  string loja; // nome da loja
  string fichClientes, fichProdutos, fichTransacoes; // nome dos
						     // ficheiros de
						     // clientes,
						     // produtos e
						     // transacoes
  bool transacoesAlterdas; // flag que fica a true se for preciso guardar no final as transacoes
  bool clientesAlterados; // flag que fica a true se for preciso guardar no final os clienets
  unsigned int maxClientesId; // variavel que guarda o identificador unico do cliente com o maior identiicador
  vector<Cliente> clientes; // vetor que guarda a informacao dos clientes existentes
  vector<Produto> produtos; // vetor que guarda a informacao dos produtos disponiveis
  vector<Transacao> transacoes; // vetor que guarda a informacao das ttransacoes efetuadas
  map<string, int> clienteIdx;  // map para "traduzir" nome do cliente no indice dele no vetor de clientes
  map<string, int> produtoIdx;  // map para "traduzir" nome do produto no indice dele no vetor de produtos
  map<unsigned int, vector<string>> clienteProdx; // map para "traduzir" o id do
				   // cliente no vetor de TODOS os produtos por ele comprados
  //map<string, unsigned int> produtoRecomendacaoFrequenciax;
  vector<string> produto;
  vector<unsigned int> quantidade;

  map<string, unsigned int> produtoRecomendacaoFrequenciaBottom10x;//associa um produto de recomendacao ao numero de vezes total comprado por todos os Bottom10

 
 public:
  VendeMaisMais();
  VendeMaisMais(string loja, string fichClients, string fichProdutos, string fichTransacoes);
  void preencheMapCliente(string nome);
  void preencheMapClienteProd();
  void preencheMapProduto(string nome);
  void preencheMapProdutoRecomendacaoFrequencia(vector<string> &produtosRecomendacao);
  void preencheMapProdutoFrequenciaBottom10(vector<string> &produtosRecomendacaoPorOrdemFrequencia, vector<Cliente> &Bottom10);
  void listarClientesOrdemAlfa() const;
  void listarProdutos() const;
  void mostraInformacaoCliente(string nome) const;
  void mostraInformacaoTodosClientes() const;
  void criarCliente(unsigned int id, string nome, Data cartaoCliente, float volCompras);
  void editarCliente(unsigned int idCheck, unsigned int id, string nome, float volCompras, Data cartaoCliente);
  void removerCliente(string nome);
  void mostrarTransacoesDataEspecifica(Data data) const;
  void mostrarTransacoesEntreDatas(Data dataAntiga, Data dataRecente) const;
  void adicionarTransacao(unsigned int id, Data d, string listaProdutos);
  void mostraTransacoesCliente(string nome) const;
  void mostraTodasTransacoes() const;
  void fillProductsVector(ifstream &stream);//preenche o vetor de produtos
  void fillTransactionsVector(ifstream &stream);//preenche o vetor de transacoes
  void fillClientsVector(ifstream &stream);//preenche o vetor de clientes
  void recomendarCliente();
  void verBottom10();
  void recomendarBottom10();
  friend bool comparaProdutoFreq(string &p1, string &p2);
  unsigned int quantasVezesComprou(unsigned int idCliente, string produto);
  void saveChanges();
  
  void show();
};
