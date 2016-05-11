#include "Vende++.h"


VendeMaisMais::VendeMaisMais(string loja, string fichClients, string fichProdutos, string fichTransacoes){

  // A IMPLEMENTAR 
}

/*********************************
 * Gestao de Clientes
 ********************************/  

void VendeMaisMais::fillClientsVector(ifstream &stream)//preenche o vetor de clientes
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
			Data date = Data(line.substr(index2 + 2, (index3 - 1) - (index2 + 2)));
			float value = stof(line.substr(index3 + 2));
			Cliente c = Cliente(id, name, date, value);
			clientes.push_back(c);
			lineCount++;
		}
	}
}//afinal esta funcao tem de estar aqui, e nao em utils.cpp, porque sendo o vetor de clientes private à classe Cliente, so se pode
// aceder a esse vetor numa funcao que seja membro da classe em causa. (se pusesse em utils.cpp nao conseguia chamar posteriormente 
// a funcao fillClientsVector na main, porque o parametro vetor de clientes que ia necessitar é considerado inacessível)

// lista os clientes por ordem alfabetica crescente
void VendeMaisMais::listarClientesOrdemAlfa() const{

  // A IMPLEMENTAR 

}

// mostra a informacao individual de um cliente
void VendeMaisMais::mostraInformacaoCliente(string nome){



}

/*********************************
 * Gestao de Produtos
 ********************************/  

// lisat os produto por ordem alfabetica crescente
void VendeMaisMais::listarProdutos() const{

  // A IMPLEMENTAR 

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
