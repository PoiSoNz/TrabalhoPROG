#include "Transacao.h"



unsigned int Transacao::getIdCliente() const{
  return idCliente;
}

Transacao::Transacao(ifstream & in){ // le uma transacao na forma de  idcliente ; data ; lista produtos
  // A IMPLEMENTAR
}

Transacao::Transacao(unsigned int idCliente, Data data, vector<string> produtos)
{
	this->idCliente = idCliente;
	this->data = data;
	this->produtos = produtos;
}


void Transacao::save(ofstream & out) const{ // transacao guardada como na forma de  idcliente ; data ; lista produtos
  // A IMPLEMENTAR
}

ostream& operator<<(ostream& out, const Transacao & trans){

  // A IMPLEMENTAR
}
