#include "Cliente.h"


Cliente::Cliente(ifstream &in){//Consideramos o ID igual a zero, data de adesao 0/0/0 e volume de compras igual a zero.
	id = 0;
	nome = "";
	cartaoCliente.setDia(0);
	cartaoCliente.setMes(0);
	cartaoCliente.setAno(0);
	volCompras = 0;
}

Cliente::Cliente(unsigned int id, string nome, Data cartaoCliente, float volCompras)
{

}


string Cliente::getNome() const{
  return nome;
}

unsigned int Cliente::getId() const{
  return id;
}

float Cliente::getVolCompras() const{
  return volCompras;
}

void Cliente::save(ofstream &out) const{

  // A IMPLEMENTAR

}

ostream& operator<<(ostream& out, const Cliente &cli){
  // A IMPLEMENTAR
}


bool operator<(const Cliente &cli1, const Cliente &cli2){
  // A IMPLEMENTAR
}
