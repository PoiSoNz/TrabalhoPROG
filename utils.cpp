#include "utils.h"


void clearScreen(){
  // A IMPLEMENTAR
}


unsigned short int leUnsignedShortInt(unsigned short int min, unsigned short int  max){
	unsigned short int escolha;
	cin >> escolha;
	while (cin.fail()||(escolha < min || escolha > max))
	{
		cout << "Tente novamente: ";
		cin >> escolha;
	}
	return escolha;
}


int leInteiro(int min, int max){
	return 9; //!!!!
	// A IMPLEMENTAR

}


void checkFile(ifstream &stream, string nomeFicheiro)//verifica se um ficheiro foi lido com sucesso e caso contrario vai pedindo um nome de ficheiro valido
{
	stream.open(nomeFicheiro);
	while (!stream.is_open())
	{
		cout << "O ficheiro" << "\"" << nomeFicheiro << "\"" << " nao foi encontrado." << endl << endl;
		cout << "Insira novamente o nome do ficheiro: ";
		cin >> nomeFicheiro;
		stream.open(nomeFicheiro);
	}
	cout << "O ficheiro foi lido com sucesso! ";
}


void extractProducts(vector<string> vetor, string listaprodutos)
{
	while (listaprodutos != "")
	{
		unsigned int index = listaprodutos.find_first_of(',');
		string produto = listaprodutos.substr(0, index);
		vetor.push_back(produto);
		extractProducts(vetor, listaprodutos.substr(index + 2));
	}
}

void lowerCase(string &s)
{
	for (int i = 0; i < s.length(); i++)
	{
		s[i] = tolower(s[i]);
	}
}

void trim(string &s)
{
	if ((int)s[0] == 32) //codigo ascii do espaço é 32
	{
		s.erase(0, 1);
		trim(s);
	}

	if ((int)s[s.size() - 1] == 32)
	{
		s.erase(s.size() - 1, 1);
		trim(s);
	}

	for (int i = 1; i<s.size(); i++)
	{
		if ((int)s[i] == 32 && s[i] == s[i + 1])
			s.erase(i, 1);
	}
}

int encontraPosicao(string s, char *c, unsigned int num)// retorna a posição do numº caracter *c na string s
{
	int contador = 0;
	for (int i = 0; i<s.size(); i++)
	{
		if (s[i] == *c)
			contador++;

		if (contador == num)
			return i;
	}
}
