#include "Data.h"


Data::Data(string dataStr){ // data na forma DD/MM/AAA
	int barra1 = dataStr.find_first_of('//');
	int barra2 = dataStr.find_last_of('//');
	this->dia = stoi(dataStr.substr(0, barra1));
	this->mes = stoi(dataStr.substr(barra1 + 1, barra2));
	this->ano = stoi(dataStr.substr(barra2 + 1));
}

Data::Data(int dia, int mes, int ano){// data dividida em dia, mes, ano
	this->dia = dia;
	this->mes = mes;
	this->ano = ano;
}	

int Data::getDia() const{
  return dia;
}

int Data::getMes() const{
  return mes;
}

int Data::getAno() const{
  return ano;
}

void Data::setDia(int dia){
	this->dia = dia;
}

void Data::setMes(int mes){
	this->mes = mes;
}

void Data::setAno(int ano){
	this->ano = ano;
}

void Data::save(ofstream & out) const{
  // A IMPLEMENTAR
}

ostream& operator<<(ostream& out, const Data & data){
  // A IMPLEMENTAR
}
