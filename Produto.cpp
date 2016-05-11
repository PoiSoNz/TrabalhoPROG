#include "Produto.h"


Produto::Produto(ifstream & in){ // nome ; custo
}

Produto::Produto(){//Um produto criado por omissão não tem nome e tem custo zero.
	nome="";
	custo=0;
}

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
