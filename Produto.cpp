#include "Produto.h"
#include "utils.h"
#include <iomanip>


Produto::Produto() {//Um produto criado por omissao nao tem nome(string vazia) e tem custo zero.
	nome = "";
	custo = 0;
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

ostream& operator<<(ostream& out, const Produto &prod){
	out << setw(5) << left << prod.getNome() << setw(25) << fixed << setprecision(2) << prod.getCusto();
	out.unsetf(ios_base::floatfield);
	return out;
}


bool operator<(const Produto &prod1, const Produto &prod2){
	string nome1 = prod1.getNome();
	string nome2 = prod2.getNome();
	lowerCase(nome1);
	lowerCase(nome2);
	const char *nomeProduto1 = nome1.c_str();//converte o nome de cada um dos clientes para uma string de C
	const char *nomeProduto2 = nome2.c_str();//para poder usar como argumentos da funcao strcmp

	if ((strcmp(nomeProduto1, nomeProduto2)) < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
