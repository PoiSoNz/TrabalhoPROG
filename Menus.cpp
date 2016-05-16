#include "Menus.h"


bool infoInicial(string & loja, string & fichClientes, string & fichProdutos, string & fichTransacoes){
	return true; //!!!!aqui foi so pra poder compilar
}


/******************************************
 * Gestao de Clientes
 ******************************************/
unsigned short int menuGestaoClientes(){
  unsigned short int opcao;

  clearScreen();
  cout << TAB_BIG << "Menu Gestao Clientes" << endl;
  cout << endl;
  cout << TAB << "1 - Listar clientes por ordem alfabetica" << endl;
  cout << TAB << "2 - Ver informacao de um cliente" << endl;
  cout << TAB << "3 - Ver informacao de todos os clientes" << endl;
  cout << TAB << "4 - Criar cliente" << endl;
  cout << TAB << "5 - Editar cliente" << endl;
  cout << TAB << "6 - Remover cliente" << endl;
  cout << TAB << "7 - Voltar ao menu inicial" << endl << endl;
  cout << TAB << "Qual a sua opcao: ";
  opcao = leUnsignedShortInt(1, 7);

  if(opcao == 7)
    return 0;

  return opcao;
}


void opcoesGestaoClientes(VendeMaisMais & supermercado){
  unsigned int opcao;
  string nome;
  unsigned int idCheck, newId, id;
  string newName, newCartaoCliente, name, data;
  float newVolCompras, compras;
  while((opcao = menuGestaoClientes()))

    switch (opcao){
    case 1: supermercado.listarClientesOrdemAlfa();
      break;
    case 2: cout << "Qual o nome do cliente: ";
	  cin.ignore();
      getline(cin, nome);
      supermercado.mostraInformacaoCliente(nome);
      break;
	case 3: supermercado.mostraInformacaoTodosClientes();
      break;
    case 4: cout << "Qual o id do cliente: ";
		cin >> id;
		while (cin.fail() || id < 0)
		{
			cin.ignore();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Tente novamente: ";
			cin >> id;
		}
		cout << "Qual o nome do cliente: ";
      cin.ignore();
	  getline(cin, name);
	  cout << "Qual a nova data de adesao do cliente (DD/MM/AAAA): ";
	  cin >> data;
	  //cin.ignore();
	  //getline(cin, data);
	  cout << "Qual o volume de compras do cliente: ";
	  cin >> compras;
	  while (cin.fail() || compras < 0)
	  {
		  cin.clear();
		  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		  cout << "Tente novamente: ";
		  cin >> compras;
	  }
	  supermercado.criarCliente(id, name, data, compras);
      break;
	case 5: 
	  cout << "Qual o id do cliente: ";
	  cin >> idCheck;
	  while (cin.fail() || idCheck < 0)
	  {
		  cin.ignore();
		  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		  cout << "Tente novamente: ";
		  cin >> idCheck;
	  }
	  cout << "Qual o novo id do cliente: ";
	  cin >> newId;
	  while (cin.fail() || newId < 0)
	  {
		  cin.clear();
		  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		  cout << "Tente novamente: ";
		  cin >> newId;
	  }
	  cout << "Qual o novo nome do cliente: ";
	  cin.ignore();
	  getline(cin, newName);
	  cout << "Qual a nova data de adesao do cliente (DD/MM/AAAA): ";
	  cin >> data;
	  cout << "Qual o novo volume de compras do cliente: ";
	  cin >> newVolCompras;
	  while (cin.fail() || newVolCompras < 0)
	  {
		  cin.clear();
		  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		  cout << "Tente novamente: ";
		  cin >> newVolCompras;
	  }
	  supermercado.editarCliente(idCheck, newId, newName, newVolCompras, newCartaoCliente);
	  break;
	case 6: cout << "Qual o nome do cliente: ";
	  cin.ignore();
	  getline(cin, nome);
	  supermercado.removerCliente(nome);
      break;
    }
}

/******************************************
 * Gestao de Transacoes
 ******************************************/
unsigned short int menuGestaoTransacoes(){
	unsigned short int opcao;

	clearScreen();
	cout << TAB_BIG << "Menu Gestao Transacoes" << endl;
	cout << endl;
	cout << TAB << "1 - Efetuar compras" << endl;
	cout << TAB << "2 - Listar transacoes de um cliente por ordem cronologica" << endl;
	cout << TAB << "3 - Listar transacoes de uma data especifica" << endl;
	cout << TAB << "4 - Listar transacoes num intervalo de tempo" << endl;
	cout << TAB << "5 - Listar todas as transacoes" << endl;
	cout << TAB << "6 - Voltar ao menu inicial" << endl << endl;
	cout << TAB << "Qual a sua opcao: ";
	opcao = leUnsignedShortInt(1, 6);

	if (opcao == 6)
		return 0;

	return opcao;
}

void opcoesGestaoTransacoes(VendeMaisMais & supermercado){
  unsigned int opcao;

  while((opcao = menuGestaoTransacoes()))
    switch (opcao){
    case 1:
      break;
    case 2:
      break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
    }
}

/******************************************
 * Recomendacoes
 ******************************************/

unsigned short int menuRecomendacao(){
	return 9; //!!!
}


void opcoesRecomendacao(VendeMaisMais & supermercado){
  unsigned int opcao;

  while((opcao = menuRecomendacao()))
    switch (opcao){
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    }

}

/******************************************
 * Menu Inicial
 ******************************************/
unsigned short int menuInicial(){
  unsigned short int opcao;

  clearScreen();
  cout << TAB_BIG << "Menu Inicial" << endl;
  cout << endl;
  cout << TAB << "1 - Gestao de clientes" << endl;
  cout << TAB << "2 - Lista produto disponiveis" << endl;
  cout << TAB << "3 - Gestao de transacoes" << endl;
  cout << TAB << "4 - Recomendacoes" << endl;
  cout << TAB << "5 - Sair do programa" << endl << endl;
  cout << TAB << "Qual a sua opcao: ";
  opcao = leUnsignedShortInt(1, 5);

  if(opcao == 5)
    return 0;

  return opcao;
}

void opcoesIniciais(VendeMaisMais & supermercado){
  unsigned int opcao;


  while((opcao = menuInicial()))
    switch (opcao){
    case 1: opcoesGestaoClientes(supermercado);
      break;
    case 2: supermercado.listarProdutos();
      break;
    case 3: opcoesGestaoTransacoes(supermercado);
      break;
    case 4: opcoesRecomendacao(supermercado);
      break;
    }

  supermercado.saveChanges();
}
