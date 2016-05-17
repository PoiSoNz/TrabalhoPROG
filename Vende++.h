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
  multimap<int, int> transacaoIdx; // multima para "traduzir" o identificador do
				   // cliente nos indices das suas
				   // transacoes no vetor de
				   // transacoes

 public:
  VendeMaisMais();
  VendeMaisMais(string loja, string fichClients, string fichProdutos, string fichTransacoes);
  void listarClientesOrdemAlfa() const;
  void listarProdutos() const;
  void mostraInformacaoCliente(string nome) const;
  void mostraInformacaoTodosClientes() const;
  void criarCliente(unsigned int id, string nome, string cartaoCliente, float volCompras);
  void editarCliente(unsigned int idCheck, unsigned int id, string nome, float volCompras, string cartaoCliente);
  void removerCliente(string nome);
  void VendeMaisMais::mostrarTransacoesDataEspecifica(Data data) const;
  void VendeMaisMais::mostrarTransacoesEntreDatas(Data dataAntiga, Data dataRecente) const;
  void saveChanges() const;
  void fillProductsVector(ifstream &stream);//preenche o vetor de produtos
  void fillTransactionsVector(ifstream &stream);//preenche o vetor de transacoes
  void fillClientsVector(ifstream &stream);//preenche o vetor de clientes

  friend ostream& operator<<(ostream& out, const VendeMaisMais & supermercado);
};
