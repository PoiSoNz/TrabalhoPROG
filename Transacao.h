#pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

#include "Data.h"



using namespace std;


class Transacao { 
 private:
  unsigned int idCliente;
  Data data; // na forma DD/MM/AAAAA
  vector<string> produtos;

 public:
  Transacao(ifstream & in); // trabsacao na forma de  idCliente ; data ; lista de produtos
  Transacao();
  Transacao(unsigned int idCliente, Data data, vector<string> produtos);
  unsigned int getIdCliente() const;
  Data getData() const;
  string getProdutos() const;
  void save(ofstream & out) const; // guarda a transacao

  friend ostream& operator<<(ostream& out, const Transacao & trans); // mostra a transacao
};



