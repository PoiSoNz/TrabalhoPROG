#include "Transacao.h"



unsigned int Transacao::getIdCliente() const{
  return idCliente;
}



Transacao::Transacao(ifstream & in){ // le uma transacao na forma de  idcliente ; data ; lista produtos
  // A IMPLEMENTAR
}

void Transacao::save(ofstream & out) const{ // transacao guardada como na forma de  idcliente ; data ; lista produtos
  // A IMPLEMENTAR
}


ostream& operator<<(ostream& out, const Transacao & trans){

  // A IMPLEMENTAR
}
