#include "Produto.h"


Produto::Produto(ifstream & in){ // nome ; custo
	nome = "";
	custo = 0;
}//Consideramos o nome com string vazia e o custo igual a zero.

Produto::Produto(string nome, float custo)
{
	this->nome = nome;
	this->custo = custo;
}

string Produto::getNome() const {
  return nome;
}

float Produto::getCusto() const {
  return custo;
}

ostream& operator<<(ostream& out, const Produto & prod){


  // A IMPLEMENTAR

}


bool operator<(const Produto &prod1, const Produto &prod2){
  // A IMPLEMENTAR
}
