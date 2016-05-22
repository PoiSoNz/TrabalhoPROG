#include "Transacao.h"


Transacao::Transacao() {//Uma transação criada por omissao terá um id igual a zero, data igual a 0/0/0 e nenhum produto
	vector<string> vetor;
	Data d;
	idCliente = 0;
	data = d;
	produtos = vetor;
}

Transacao::Transacao(unsigned int idCliente, Data data, vector<string> produtos)
{
	this->idCliente = idCliente;
	this->data = data;
	this->produtos = produtos;
}

unsigned int Transacao::getIdCliente() const {
	return idCliente;
}

Data Transacao::getData() const
{
	return data;
}

string Transacao::getProdutos() const
{
	string stringProdutos = "";
	for (int i = 0; i < produtos.size(); i++)
	{
		if (i != produtos.size() - 1)
		{
			stringProdutos.append(produtos[i] + ", ");
		}
		else
		{
			stringProdutos.append(produtos[i]);
		}
	}
	return stringProdutos;
}

void Transacao::save(ofstream & out) const { // transacao guardada como na forma de  idcliente ; data ; lista produtos
											 // A IMPLEMENTAR
}

ostream& operator<<(ostream& out, const Transacao & trans) {
	out << setw(5) << left << trans.getIdCliente() << setw(12) << left << trans.getData() << trans.getProdutos();
	return out; 
}

