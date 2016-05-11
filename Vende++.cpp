#include "Vende++.h"


VendeMaisMais::VendeMaisMais(string loja, string fichClients, string fichProdutos, string fichTransacoes){

  // A IMPLEMENTAR 
}

/*********************************
 * Gestao de Clientes
 ********************************/  

void VendeMaisMais::fillClientsVector(ifstream &stream)
{
	string line;
	int lineCount = 0;
	while (getline(stream, line))
	{
		if (!lineCount == 0)
		{
			int index1 = line.find_first_of(';');
			int index2 = (line.substr(index1)).find_first_of(';');
			int index3 = line.find_last_of(';');
			unsigned int id = stoi(line.substr(0, index1 - 1));
			string name = line.substr(index1 + 2, (index2 - 1) - (index1 + 2));
			trim(name);
			Data date = Data(line.substr(index2 + 2, (index3 - 1) - (index2 + 2)));
			float value = stof(line.substr(index3 + 2));
			Cliente c = Cliente(id, name, date, value);
			clientes.push_back(c);
			lineCount++;
		}
	}
}

// lista os cleinets por ordem alfabetica crescente
void VendeMaisMais::listarClientesOrdemAlfa() const{

  // A IMPLEMENTAR 

}

// mostra a informacao individual de um cliente
void VendeMaisMais::mostraInformacaoCliente(string nome){



}

/*********************************
 * Gestao de Produtos
 ********************************/  

void VendeMaisMais::fillProductsVector(ifstream &stream)
{
	string line;
	int lineCount = 0;
	while (getline(stream, line))
	{
		if (!lineCount == 0)
		{
			int index1 = line.find_first_of(';');
			string nome = line.substr(0, index1 - 1);
			float custo = stoi(line.substr(index1 + 2));
			Produto p = Produto(nome, custo);
			produtos.push_back(p);
			lineCount++;
		}
	}
}

// lisat os produto por ordem alfabetica crescente
void VendeMaisMais::listarProdutos() const{

  // A IMPLEMENTAR 

}

/*********************************
* Gestao de Transacoes
********************************/

void VendeMaisMais::fillTransactionsVector(ifstream &stream)
{
	string line;
	int lineCount = 0;
	while (getline(stream, line))
	{
		if (!lineCount == 0)
		{
			int index1 = line.find_first_of(';');
			int index2 = line.find_last_of(';');
			unsigned int id = stoi(line.substr(0, index1 - 1));
			Data date = Data(line.substr(index1 + 2, (index2 - 1) - (index1 + 2)));
			vector<string> vetor;
			extractProducts(vetor, line.substr(index2 + 2));
			Transacao t = Transacao(id, date, vetor);
			transacoes.push_back(t);
			lineCount++;
		}
	}
}

/*********************************
 * Preservar Informacao
 ********************************/  

// guarda apenas a informacao de clientes e/ou de transacoes que foi alterada
void VendeMaisMais::saveChanges() const{

  // A IMPLEMENTAR 

}

/*********************************
 * Mostrar Loja
 ********************************/  

// mostra o conteudo de uma loja
ostream& operator<<(ostream& out, const VendeMaisMais & supermercado){

  // A IMPLEMENTAR 

}

