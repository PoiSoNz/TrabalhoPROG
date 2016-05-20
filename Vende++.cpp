#include "Vende++.h"


VendeMaisMais::VendeMaisMais(string loja, string fichClients, string fichProdutos, string fichTransacoes){
	this->loja=loja;
	this->fichClientes=fichClientes;
	this->fichProdutos=fichProdutos;
	this->fichTransacoes=fichTransacoes;
}

/*********************************
 * Gestao de Clientes
 ********************************/  

void VendeMaisMais::fillClientsVector(ifstream &stream)
{
	string line;
	int lineCount = 0;
	while (getline(stream, line))
	{
		if (!lineCount == 0)
		{
			int index1 = line.find_first_of(';');
			int index2 = (line.substr(index1+1)).find_first_of(';')+(line.substr(0,index1+1)).length();//correcao
			int index3 = line.find_last_of(';');
			unsigned int id = stoi(line.substr(0, index1 - 1));
			string name = line.substr(index1 + 2, (index2 - 1) - (index1 + 2));
			trim(name);
			Data date = Data(line.substr(index2 + 2, (index3 - 1) - (index2 + 2)));
			float value = stof(line.substr(index3 + 2));
			Cliente c = Cliente(id, name, date, value);
			clientes.push_back(c);
			lineCount++;
		}
	}
}

// lista os cleinets por ordem alfabetica crescente
void VendeMaisMais::listarClientesOrdemAlfa() const{

  // A IMPLEMENTAR 

}

// mostra a informacao individual de um cliente
void VendeMaisMais::mostraInformacaoCliente(string nome){



}

/*********************************
 * Gestao de Produtos
 ********************************/  

void VendeMaisMais::fillProductsVector(ifstream &stream)
{
	string line;
	int lineCount = 0;
	while (getline(stream, line))
	{
		if (!lineCount == 0)
		{
			int index1 = line.find_first_of(';');
			string nome = line.substr(0, index1 - 1);
			float custo = stoi(line.substr(index1 + 2));
			Produto p = Produto(nome, custo);
			produtos.push_back(p);
			lineCount++;
		}
	}
}

// lisat os produto por ordem alfabetica crescente
void VendeMaisMais::listarProdutos() const{
	cout<<"Produtos"<<endl;
	cout<<"---------------------"<<endl;
for( int i = 0; i<produtos.size(); i++)
{
	cout<<produtos[i]<<endl;
}
cout<<endl;

}

/*********************************
* Gestao de Transacoes
********************************/

void VendeMaisMais::fillTransactionsVector(ifstream &stream)
{
	string line;
	int lineCount = 0;
	while (getline(stream, line))
	{
		if (!lineCount == 0)
		{
			int index1 = line.find_first_of(';');
			int index2 = line.find_last_of(';');
			unsigned int id = stoi(line.substr(0, index1 - 1));
			Data date = Data(line.substr(index1 + 2, (index2 - 1) - (index1 + 2)));
			vector<string> vetor;
			extractProducts(vetor, line.substr(index2 + 2));
			Transacao t = Transacao(id, date, vetor);
			transacoes.push_back(t);
			lineCount++;
		}
	}
}

void VendeMaisMais::showAllTransaction(){
	cout<<"ID   Data        Produtos Comprados"<<endl;
	cout<<"-----------------------------------"<<endl;
	for( int i=0; i<transacoes.size(); i++)
	{
		cout<<setw(5)<<left<< transacoes[i].getIdCliente();
		cout << setw(12)<<left<< transacoes[i].getData();
		
		for (int j=0; j<transacoes[i].getProdutos().size(); j++ )//percorre o vetor de produtos de uma transacao
		{
			if(j!= transacoes[i].getProdutos.produtosTransacao.size() - 1)
			{
			cout<< transacoes[i].getProdutos().produtosTransacao[j];
			cout<<", ";
			}
			else cout<< transacoes[i].getProdutos().produtosTransacao;
			
		}
		
		
	}
}

void VendeMaisMais::mostrarTransacoesDataEspecifica (Data data) {
	
	while (!verifyData(data.getDia(), data.getMes(), data.getAno()))
	{
		string date;

		cout << "A data que introduziu e invalida!" << endl;
		cout << "Introduza novamente: ";
		cin >> date;
		Data d(date);
		data = d;
	}

	int transacoesMostradas; //Numero de transacoes mostradas no ecra

	cout << "Transacoes do dia " << data << endl << endl;
	cout << "ID   Produtos Comprados" << endl;
	cout << "-----------------------" << endl;

	for (int i = 0; i < transacoes.size(); i++)
	{
		if (transacoes[i].getData() == data)
		{
			cout << setw(5) << left << transacoes[i].getid() << setw(50) << left << transacoes[i].getprodutos() << endl;
			transacoesMostradas++;
		}
	}

	if (transacoesMostradas == 0)
		cout << "Lamentamos mas nao foram encontradas quaisquer transacoes na data introduzida!";

}

void VendeMaisMais::mostrarTransacoesEntreDatas(Data dataAntiga, Data dataRecente) { //A dataAntiga é mais antiga do que a dataRecente

	while ( !verifyData( dataAntiga.getDia(), dataAntiga.getMes(), dataAntiga.getAno() ) )
	{
		string date;

		cout << "A data mais antiga que introduziu e invalida!" << endl;
		cout << "Introduza novamente: ";
		cin >> date;
		Data d(date);
		dataAntiga = d;
	}

	while ( !verifyData( dataRecente.getDia(), dataRecente.getMes(), dataRecente.getAno() ) )
	{
		string date;

		cout << "A data mais recente que introduziu e invalida!" << endl;
		cout << "Introduza novamente: ";
		cin >> date;
		Data d(date);
		dataRecente = d;
	}

	while (!verifyDatesOrder(dataAntiga.getDia(), dataAntiga.getMes(), dataAntiga.getAno(), dataRecente.getDia(), dataRecente.getMes(), dataRecente.getAno()))
	{
		string dateAnterior;
		string datePosterior;

		cout << "As datas que introduziu encontram-se trocadas cronologicamente!" << endl;
		cout << "Introduza novamente a data mais antiga: ";
		cin >> dateAnterior;
		cout << "Introduza novamente a data mais recente: ";
		cin >> datePosterior;

		Data d1(dateAnterior);
		Data d2(datePosterior);

		mostrarTransacoesEntreDatas(d1, d2); //Chama a funcao novamente para verificar se as novas datas introduzidas sao validas
	}

	
	int transacoesMostradas; //Numero de transacoes mostradas no ecra

	cout << "Transacoes desde " << dataAntiga << " ate " << dataRecente << endl << endl;
	cout << "ID   Produtos Comprados" << endl;
	cout << "-----------------------" << endl;

	for (int i = 0; i < transacoes.size(); i++)
	{
		if (! ((transacoes[i].getAno() >= dataAntiga.getAno() ) && (transacoes[i].getAno <= dataRecente.getAno())))//se o ano de uma transacao é mais antigo do que o ano da data antiga OU é mais recente do que o ano da data recente, entao certamente NAO estara entre as duas datas
		{
		}
		else if ((transacoes[i].getAno() > dataAntiga.getAno() ) && (transacoes[i].getAno() < dataRecente.getAno())) // se o ano de uma transacao é mais recente do que o ano da data antiga E é mais antigo do que o ano da data recente, entao certamente ESTARA entre as duas datas
		{
			cout << setw(5) << left << transacoes[i].getid() << setw(50) << left << transacoes[i].getprodutos() << endl;
			transacoesMostradas++;

			

		}
		else if (!((transacoes[i].getMes() >= dataAntiga.getMes()) && (transacoes[i].getMes <= dataRecente.getMes()))) //Depois do que ja foi verificado se o mes de uma transacao é menor do que o mes da data antiga OU é maior do que o mes da data recente, entao certamente NAO estara entre as duas datas
		{
		}
		else if ((transacoes[i].getMes() > dataAntiga.getMes()) && (transacoes[i].getMes() < dataRecente.getMes())) //Depois do que ja foi verificado se o mes de uma transacao é maior do que o mes da data antiga E é menor do que o mes da data recente, entao certamente ESTARA entre as duas datas
		{
			cout << setw(5) << left << transacoes[i].getid() << setw(50) << left << transacoes[i].getprodutos() << endl;
			transacoesMostradas++;

		}
		else if ((transacoes[i].getDia() >= dataAntiga.getDia()) && (transacoes[i].getDia() <= dataRecente.getDia())) //Depois do que ja foi verificado se o dia de uma transacao é maior ou igual ao o mes da data antiga E é menor ou igual ao mes da data recente, entao certamente ESTARA entre as duas datas CASO CONTRARIO NAO ESTARA
		{
			cout << setw(5) << left << transacoes[i].getid() << setw(50) << left << transacoes[i].getprodutos() << endl;
			transacoesMostradas++;

		}

	}

	if(transacoesMostradas==0)
		cout<< "Lamentamos mas nao foram encontradas quaisquer transacoes entre as datas introduzidas!";



}

void advertisment(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector)
{
	/*MATRIX CREATION------------------------------------------------------------------------------------------------------------*/
	vector<vector<bool>> matrix;

	for (int i = 0; i < clientsVector.size(); i++)
	{
		vector<bool>productsLine;

		for (int j = 0; j < productsVector.size(); j++)
		{
			productsLine.push_back(checkProduct(clientsVector.at(i).clientID, productsVector.at(j), transactionsVector));
		}
		matrix.push_back(productsLine);
	}
	/*-----------------------------------------------------------------------------------------------------------------------------*/
	unsigned int id;

	cout << "Introduce the ID whose client you want to advertise" << endl << endl;
	cout << "ID: ";
	cin >> id;//ID of the advertised client


	string advertismentList;//Productsthat will be advertised

	int advertisedPosition;//Matrix line position of the advertised client(it corresponds to his position on the clients vector)

	advertisedPosition = clientVectorPosition(id, clientsVector); // position the advertised client occupies on both clients' vector and matrix(they are both the same)

	if (advertisedPosition == 1000)
	{
		int operation;

		cout << "Such ID does not exists!" << endl << endl;
		cout << "Select what you want to do:" << endl;
		cout << "1. Advertise a new client" << endl;
		cout << "2. Quit to main menu" << endl;
		cout << "Chosen operation: ";
		cin >> operation;

		cout << endl;

		switch (operation)
		{
		case 1:
			advertisment(clientsVector, transactionsVector, productsVector);
		case 2:
			optionsMenu(clientsVector, transactionsVector, productsVector);
		}
	}

	for (int i = 0; i < clientsVector.size(); i++)//We will run through the matrix vector(it has the same number of lines has the clients lines)
	{
		int commonProducts = 0;//How many products the advertised client and another one have bought in common
		int nonCommonProducts = 0;//How many products another client has, but the advertised one doedn't

		if (i != advertisedPosition)
		{
			for (int j = 0; j < matrix.at(i).size(); j++)//Counts how much common and non common products there bewteen a client and the advertised one
			{
				if (matrix.at(i).at(j) == matrix.at(advertisedPosition).at(j) && true)//if a client and the advertised one have the same product
				{
					commonProducts++;
				}
				else if (matrix.at(i).at(j)==true && !matrix.at(advertisedPosition).at(j))//if a client has a product that the advertised one doesn't, then we will increase one on the nonCommonProducts variable
				{
					nonCommonProducts++;
				}
			}

			//I will consider similar shopping habbits, if two people have bought at least 2 items in common

			if (commonProducts >= 2 && nonCommonProducts > 0)//if a client has bought at least the same 2 items has the advertised one, and has also bought something that the advertised one didnt, then the items bought by the given client but not the advertised one will go into the advertisment list
			{
				for (int j = 0; j < matrix.at(i).size(); j++)
				{
					if (matrix.at(i).at(j)==true && !matrix.at(advertisedPosition).at(j))//the products that a given client has but the advertised one doesn't are put in a list
					{
						if (advertismentList.find(productsVector.at(j)) == string::npos)//If the product isn't already on the advertisment list, then it will be added
						{
							advertismentList.append(productsVector.at(j));
							advertismentList.append(", ");
						}
					}

				}
			}

		}

	}

	advertismentList.erase(advertismentList.size() - 2, 2);//to erase the last semicolon and space

	cout << clientsVector.at(advertisedPosition).clientNAME;
	cout << ", why don't you take a look at our freshest products!" << endl;
	cout << advertismentList<<endl<<endl;

	optionsMenu(clientsVector, transactionsVector, productsVector);

}

bool checkProduct(unsigned int clientId, string product, vector<transaction_t>&transactionsVector)
{//verifies if a given client(ID) bought a given product
	for (int i = 0; i < transactionsVector.size(); i++)
	{
		if (transactionsVector.at(i).clientID == clientId)//if the id matches with the transaction id, then it will look for the product on that transaction
		{
			if (transactionsVector.at(i).transactionITEMS.find(product) != string::npos)//verifies if the product exists in a transaction
			{
				return true;
			}
		}
	}
	//if the "for" loop ends, then it means that the product wasnt found on the client transactions, so it will be returned false
	return false;
}

int clientVectorPosition(unsigned int id, vector<client_t>&clientsVector)
{//returns the position of a client on the clients' vector

	for (int i = 0; i < clientsVector.size(); i++)
	{
		if (clientsVector.at(i).clientID == id)
		{
			return i;
		}
	}
	return 1000;//If it returns 1000, it means that the client has not been found
}
/*********************************
 * Preservar Informacao
 ********************************/  

// guarda apenas a informacao de clientes e/ou de transacoes que foi alterada
void VendeMaisMais::saveChanges(string fichClientes, string fichTransacoes) const{
	
//guradar informacao no ficheiro de clientes	
		ofstream clientesStream;
		string temporary;
		clientesStream.open(fichClientes);
		clientesStream << clientes.size() << endl;

		for (int i = 0; i < clientes.size(); i++)
		{
			temporary.append(to_string(clientes[i].getId()));
			temporary.append(" ; ");
			temporary.append(clientes[i].getNome());
			temporary.append(" ; ");
			temporary.append(clientes[i].getCartaoCliente());
			temporary.append(" ; ");
			temporary.append(to_string(clientes[i].getVolCompras()));
			temporary.append("\n");
			clientesStream << temporary;
			temporary.erase();
		}
		clientesStream.close();


//guardar informacao no ficheiro de transacoes

	ofstream transacoesStream;
	string temporary;
	transacoesStream.open(fichTransacoes);
	transacoesStream << transacoes.size() << endl;

	for (int i = 0; i < transacoes.size(); i++)
	{
		temporary.append(to_string(transacoes[i].getIdCliente()));
		temporary.append(" ; ");
		temporary.append(transacoes[i].getData());
		temporary.append(" ; ");
		temporary.append(transacoes[i].getProdutos());
		temporary.append("\n");
		transacoesStream << temporary;
		temporary.erase();
	}
	transacoesStream.close();

}

/*********************************
 * Mostrar Loja
 ********************************/  

// mostra o conteudo de uma loja
ostream& operator<<(ostream& out, const VendeMaisMais & supermercado){

  // A IMPLEMENTAR 

}


