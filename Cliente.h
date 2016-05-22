#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Data.h"
//#include "utils.h"

using namespace std;


class Cliente {
 private:
  unsigned int id;
  string nome;
  Data cartaoCliente;
  float volCompras;

 public:
  Cliente::Cliente();
  Cliente(unsigned int id, string nome, Data cartaoCliente, float volCompras);
  string getNome() const;
  unsigned int getId() const;
  float getVolCompras() const;
  Data getcartaoCliente() const;
  void setNome(string nome);
  void setId(unsigned int id);
  void setVolCompras(float volCompras);
  void setcartaoCliente(Data cartaoCliente);
  friend void lowerCase(string &s);//converte cada caracter de uma string de C++ para minuscula

  void save(ofstream & out) const;
  friend ostream& operator<<(ostream& out, const Cliente & cli);  // mostra informacao do cliente no ecra
  friend bool operator<(const Cliente &cli1, const Cliente &cli2); // compara 2 clientes (1 cliente e menor que outro se o seu nome for "alfabeticamente" inferior)
};

