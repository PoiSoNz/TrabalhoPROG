#include "Cliente.h"


Cliente::Cliente(ifstream &fichClientes){//Consideramos o ID igual a zero, data de adesao 0/0/0 e volume de compras igual a zero.
	unsigned int numClientes;
	fichClientes >> numClientes;
	fichClientes.ignore();//Para que o new line a seguir ao número de clientes do ficheiro nao seja lido
	
	while(numClientes>0)
	{
		string linha;
		string id;
		string nome;
		string cartaoCliente;
		string volCompras;
		char *pontovirgula=";";
		
		getline(fichClientes, linha);
		
		int primeiroPontovirgula;
		int segundoPontovirgula;
		int terceiroPontovirgula;
		
		primeiroPontovirgula= find_first_of(";");
		segundoPontovirgula= encontraPosicao(linha, *pontovirgula, 2);
		terceiroPontovirgula= find_last_of(";");
		
		id= linha.substr(0, primeiroPontoVirgula);
		nome= linha.substr(primeiroPontovirgula + 1, segundoPontovirgula - (primeiroPontovirgula + 1));
		trim(nome);
		cartaoCliente= linha.substr(segundoPontovirgula + 1, terceiroPontovirgula - (segundoPontovirgula + 1));
		Date d(cartaoCliente);
		volCompras= linha.substr(terceiroPontovirgula + 1);
		
		Cliente c( stoi(id), nome, d, stof(volCompras));
		
		vetorClientes.push_back(c);
		
		
		
		
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
