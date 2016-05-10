#pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


using namespace std;



class Produto {
 private:
  string nome;
  float custo;


 public:
  Produto(ifstream & in);
  string getNome() const;
  float getCusto() const;
  int indiceProduto(string nome); // uso do map para "traduzir" o nome em indice no vetor de produtos
  friend ostream& operator<<(ostream& out, const Produto & prod); // ostra umproduto
  friend bool operator<(const Produto &prod1, const Produto &prod2); // compara 2 produtos (1 produto e mais pequeno que outro se o seu nome for "alfabeticamente inferior"
};


