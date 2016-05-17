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
/*********************************
 * Preservar Informacao
 ********************************/  

// guarda apenas a informacao de clientes e/ou de transacoes que foi alterada
void VendeMaisMais::saveChanges() const{

  // A IMPLEMENTAR 

}

/*********************************
 * Mostrar Loja
 ********************************/  

// mostra o conteudo de uma loja
ostream& operator<<(ostream& out, const VendeMaisMais & supermercado){

  // A IMPLEMENTAR 

}


