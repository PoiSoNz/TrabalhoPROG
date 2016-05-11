#include "Cliente.h"


Cliente::Cliente(ifstream &in){//Consideramos o ID igual a zero, data de adesao 0/0/0 e volume de compras igual a zero.
{
          		
}

Cliente::Cliente(unsigned int id, string nome, Data cartaoCliente, float volCompras)
{
	this->id=id;//***
	this->nome=nome;//***
	this->cartaoCliente=cartaoCliente;//***
	this->volCompras=volCompras;//***
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
