#include "Data.h"


Data::Data() {//Uma data criada por omissão será 0/0/0
	dia = 0;
	mes = 0;
	ano = 0;
}

Data::Data(unsigned int dia, unsigned int mes, unsigned int ano) {//Uma data criada por omissão será 0/0/0
	this->dia = dia;
	this->mes = mes;
	this->ano = ano;
}


Data::Data(string dataStr){ // data na forma DD/MM/AAA
	size_t barra1 = dataStr.find_first_of("/");
	size_t barra2 = dataStr.find_last_of("/");
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

bool operator<(const Data &data1, const Data &data2) {
	size_t dia1 = data1.getDia();
	size_t mes1 = data1.getMes();
	size_t ano1 = data1.getAno();
	size_t dia2 = data2.getDia();
	size_t mes2 = data2.getMes();
	size_t ano2 = data2.getAno();
	if (ano1 < ano2)
	{
		return true;
	}
	else if (ano1 == ano2)
	{
		if (mes1 < mes2)
		{
			return true;
		}
		else if (mes1 == mes2)
		{
			if (dia1 <= dia2)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool operator==(const Data &data1, const Data &data2) {
	if ((data1.getDia() == data2.getDia()) && (data1.getMes() == data2.getMes()) && (data1.getAno() == data2.getAno()))
	{
		return true;
	}
	else
	{
		return false;
	}
}


