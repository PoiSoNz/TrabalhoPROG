#include "Data.h"


Data::Data() {//Uma data criada por omissão será 0/0/0
	dia = 0;
	mes = 0;
	ano = 0;
}

Data::Data(string dataStr){ // data na forma DD/MM/AAA
	int barra1 = dataStr.find_first_of("/");
	int barra2 = dataStr.find_last_of("/");
	this->dia = stoi(dataStr.substr(0, barra1));
	this->mes = stoi(dataStr.substr(barra1 + 1, (barra2-(barra1-1))));
	this->ano = stoi(dataStr.substr(barra2 + 1));
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
	string date = "";
	string day = to_string(data.getDia());
	string mon= to_string(data.getMes());
	string year = to_string(data.getAno());
	date = date.append(day + "/" + mon + "/" + year);
	out << date;
	return out;
}
