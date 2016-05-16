#include "Cliente.h"
#include <iomanip>


Cliente::Cliente(){//Um cliente criado por omissao tem ID igual a zero, data de adesao 0/0/0 , volume de compras igual a zero e não tem nome
	Data d;
	id = 0;
	nome = "";
	cartaoCliente = d;
	volCompras = 0;
}

Cliente::Cliente(unsigned int id, string nome, Data cartaoCliente, float volCompras)
{
	this->id = id;
	this->nome = nome;
	this->cartaoCliente = cartaoCliente;
	this->volCompras = volCompras;
}


string Cliente::getNome() const {
	return nome;
}

unsigned int Cliente::getId() const {
	return id;
}

float Cliente::getVolCompras() const {
	return volCompras;
}

Data Cliente::getcartaoCliente() const {
	return cartaoCliente;
}

void Cliente::setNome(string nome){
	this->nome = nome;
}

void Cliente::setId(unsigned int id){
	this->id = id;
}

void Cliente::setVolCompras(float volCompras){
	this->volCompras = volCompras;
}

void Cliente::setcartaoCliente(Data cartaoCliente){
	this->cartaoCliente = cartaoCliente;
}

void Cliente::save(ofstream &out) const {

	// A IMPLEMENTAR

}

ostream& operator<<(ostream& out, const Cliente &cli) {
	out << setw(5) << left << cli.getId() << setw(25) << left << cli.getNome() << setw(12) << left << cli.getcartaoCliente() << fixed << setprecision(2) << cli.getVolCompras();
	out.unsetf(ios_base::floatfield);
	return out;
}


bool operator<(const Cliente &cli1, const Cliente &cli2) {
	string nome1 = cli1.getNome();
	string nome2 = cli2.getNome();
	lowerCase(nome1);
	lowerCase(nome2);
	const char *nomeCliente1 = nome1.c_str();//converte o nome de cada um dos clientes para uma string de C
	const char *nomeCliente2 = nome2.c_str();//para poder usar como argumentos da funcao strcmp

	if ((strcmp(nomeCliente1, nomeCliente2)) < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
