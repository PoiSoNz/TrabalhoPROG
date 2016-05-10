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
	cout << "O ficheiro foi lido com sucesso: ";
}

Cliente fillClientsVector(ifstream &stream)//
{
	string line;
	int lineCount = 0;
	while (getline(stream, line))
	{
		if (!lineCount == 0)
		{
			int index1 = line.find_first_of(';');
			int index2 = (line.substr(index1)).find_first_of(';');
			int index3 = line.find_last_of(';');
			string id = line.substr(0, index1 - 1);
			string name = line.substr(index1 + 2, (index2 - 1) - (index1 + 2));
			Data Data(line.substr(index2 + 2, (index3 - 1) - (index2 + 2)));
			string value = line.substr(index3 + 2);
			
			(esta parte é copy paste do t1 que era feito com structs)
			Cliente c;
			c.id = stoi(id);
			c.name = name;
			c.amount = stod(value);
			
			
			//VendeMaisMais::clientes.push_back(c);
			lineCount++;
		}
	}
}

