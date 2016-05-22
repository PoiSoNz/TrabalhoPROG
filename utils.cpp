#include "utils.h"
#include <algorithm>



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
		cout << "O ficheiro " << "\"" << nomeFicheiro << "\"" << " nao foi encontrado." << endl << endl;
		cout << "Insira novamente o nome do ficheiro: ";
		cin >> nomeFicheiro;
		stream.open(nomeFicheiro);
	}
	cout << "O ficheiro foi lido com sucesso! ";
	cout << endl;
}


void extractProducts(vector<string> &vetor, string listaprodutos, unsigned int counter, unsigned int numVirgulas)
{ 
	if (listaprodutos != "" && (counter < (numVirgulas+1)))
	{
		unsigned int index = listaprodutos.find_first_of(',');
		string produto = listaprodutos.substr(0, index);
		vetor.push_back(produto);
		extractProducts(vetor, listaprodutos.substr(index + 2), ++counter, numVirgulas);
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

bool clienteMontante(const Cliente c1, const Cliente c2)
{
	if (c1.getVolCompras() < c2.getVolCompras())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool clienteMontanteInvertido(const Cliente c1, const Cliente c2)
{
	if (c2.getVolCompras() < c1.getVolCompras())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool transacaoCrono(const Transacao t1, const Transacao t2)
{
	if (t1.getData() < t2.getData())//o operador < esta definido para a classe Data
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool verifyDate(int day, int month, int year)
{//Verifies if a date is valid
	bool leapYear;

	if (year % 4 == 0 && year % 100 != 0)
		leapYear = true;
	else if (year % 4 == 0 && year % 400 == 0)
		leapYear = true;
	else leapYear = false;

	if (month <= 0 || month > 12)
	{
		return false;
	}

	int leapMonths[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int notLeapMonths[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (leapYear)
	{
		if (day <= 0 || day > leapMonths[month - 1])
		{
			return false;
		}
		else return true;
	}
	else if (day <= 0 || day > notLeapMonths[month - 1])
	{
		return false;
	}
	else return true;
}

bool verifyDatesOrder(int oldDay, int oldMonth, int oldYear, int recentDay, int recentMonth, int recentYear)
{//Verifies if two given dates are respectively the older and most recent date
	if (!(oldYear <= recentYear))
	{
		return false;
	}
	if (oldYear < recentYear)//if the old year is smaller than the recent one, than it's guaranteed to be a valid date
		return true;


	if (!(oldMonth <= recentMonth))
	{
		return false;
	}
	if (oldMonth < recentMonth)  //after comparing the years if the old month is smaller than the recent one, than it's guaranteed to be a valid date
		return true;

	if (!(oldDay <= recentDay))
	{
		return false;
	}
	if (oldDay <= recentDay)////after comparing the months if the old day is smaller than the recent one, than it's guaranteed to be a valid date
		return true;
	else
	{

		return false;
	}

}

bool verifyProduct(string nome, const vector<Produto> &vec)
{
	bool flag = false;
	for (int i = 0; i < vec.size(); i++)
	{
		if (nome == vec[i].getNome())
		{
			flag = true;
		}
	}
	return flag;
}

bool verifyProduct(string nome, const vector<string> &vec)
{
	bool flag = false;
	for (int i = 0; i < vec.size(); i++)
	{
		if (nome == vec[i])
		{
			flag = true;
		}
	}
	return flag;
}

bool checkProduct(unsigned int clientId, string product, const vector<Transacao>&transactionsVector)
{//verifies if a given client(ID) bought a given product
	for (int i = 0; i < transactionsVector.size(); i++)
	{
		if (transactionsVector[i].getIdCliente() == clientId)//if the id matches with the transaction id, then it will look for the product on that transaction
		{
			if (transactionsVector[i].getProdutos().find(product) != string::npos)//verifies if the product exists in a transaction
			{
				return true;
			}
		}
	}
	//if the "for" loop ends, then it means that the product wasnt found on the client transactions, so it will be returned false
	return false;
}

int clientVectorPosition(unsigned int id, const vector<Cliente> &clientsVector)
{//returns the position of a client on the clients' vector

	for (int i = 0; i < clientsVector.size(); i++)
	{
		if (clientsVector[i].getId() == id)
		{
			return i;
		}
	}
	return 1000;//If it returns 1000, it means that the client has not been found
}

int clientVectorPosition(string nome, const vector<Cliente> &clientsVector)
{//returns the position of a client on the clients' vector

	for (int i = 0; i < clientsVector.size(); i++)
	{
		if (clientsVector[i].getNome() == nome)
		{
			return i;
		}
	}
	return 1000;//If it returns 1000, it means that the client has not been found
}

int productVectorPosition(string nome, const vector<Produto> &productsVector)
{//returns the position of a client on the clients' vector

	for (int i = 0; i < productsVector.size(); i++)
	{
		if (productsVector[i].getNome() == nome)
		{
			return i;
		}
	}
	return 1000;//If it returns 1000, it means that the client has not been found
}


string mostFrequentName(const vector<string> &vec)
{
	int maximo;
	int contador = 0;
	for (int i = 0; i < vec.size(); i++)
	{
		int contadorAtual = 0;
		for (int j = 0; j < vec.size(); j++)
		{
			if (vec[i] == vec[j])
			{
				contadorAtual++;
			}
		}
		if (contadorAtual > contador)
		{
			contador = contadorAtual;
			maximo = i;
		}
	}
	return vec[maximo];
}

float precoProduto(string produto, const vector<Produto> &vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i].getNome() == produto)
		{
			return vec[i].getCusto();
		}
	}
}

Data IntroduzaData()
{
	unsigned int dia, mes, ano;
	cout << "Dia: ";
	cin >> dia;
	while (cin.fail() || dia < 0)
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Tente novamente: ";
		cin >> dia;
	}
	cout << "Mes: ";
	cin >> mes;
	while (cin.fail() || mes < 0)
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Tente novamente: ";
		cin >> mes;
	}
	cout << "Ano: ";
	cin >> ano;
	while (cin.fail() || ano < 0)
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Tente novamente: ";
		cin >> ano;
	}
	while (!verifyDate(dia, mes, ano))
	{
		cout << "Esta data e invalida. Introduza outra: " << endl;
		cout << "Dia: ";
		cin >> dia;
		while (cin.fail() || dia < 0)
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Tente novamente: ";
			cin >> dia;
		}
		cout << "Mes: ";
		cin >> mes;
		while (cin.fail() || mes < 0)
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Tente novamente: ";
			cin >> mes;
		}
		cout << "Ano: ";
		cin >> ano;
		while (cin.fail() || ano < 0)
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Tente novamente: ";
			cin >> ano;
		}
	}
	return Data(dia, mes, ano);
}








