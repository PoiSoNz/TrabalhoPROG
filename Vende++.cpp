#include "Vende++.h"
#include <algorithm>

map<string, unsigned int> produtoRecomendacaoFrequenciax;

VendeMaisMais::VendeMaisMais() {
	this->loja = "";
	this->fichClientes = "";
	this->fichProdutos = "";
	this->fichTransacoes = "";
}

VendeMaisMais::VendeMaisMais(string loja, string fichClientes, string fichProdutos, string fichTransacoes) {
	this->loja = loja;
	this->fichClientes = fichClientes;
	this->fichProdutos = fichProdutos;
	this->fichTransacoes = fichTransacoes;
}

/*********************************
* Maps
********************************/

void VendeMaisMais::preencheMapCliente(string nome)
{
	for (int i = 0; i < clientes.size(); i++)
	{
		clienteIdx.insert(pair<string, unsigned int>(nome, clientVectorPosition(nome, clientes)));
	}
}

void VendeMaisMais::preencheMapProduto(string nome)
{
	for (int i = 0; i < produtos.size(); i++)
	{
		produtoIdx.insert(pair<string, unsigned int>(nome, productVectorPosition(nome, produtos)));
	}
}

void VendeMaisMais::preencheMapClienteProd()
{
	for (int i = 0; i < clientes.size(); i++)
	{
		vector<string> temp;
		string temporaria;
		for (int j = 0; j < transacoes.size(); j++)
		{
			if (clientes[i].getId() == transacoes[j].getIdCliente())
			{
				if (temporaria != "")
				{
					temporaria = temporaria + ", " + transacoes[j].getProdutos();
				}
				else
				{
					temporaria = temporaria + transacoes[j].getProdutos();
				}
			}
		}
		extractProducts(temp, temporaria, 0, count(temporaria.begin(), temporaria.end(), ','));
		clienteProdx.insert(pair<unsigned int, vector<string>>(clientes[i].getId(), temp));
	}
}

void VendeMaisMais::preencheMapProdutoRecomendacaoFrequencia(vector<string> &produtosRecomendacao)
{
	for (int i = 0; i < produtosRecomendacao.size(); i++)
	{
		int contador = 0;
		for (int j = 0; j < i; j++)
		{
			if (produtosRecomendacao[j] == produtosRecomendacao[i])
			{
				contador++;
			}
		}
		if (contador == 0)
		{
			unsigned int frequenciaProduto = count(produtosRecomendacao.begin(), produtosRecomendacao.end(), produtosRecomendacao[i]);
			produtoRecomendacaoFrequenciax.insert(pair<string, unsigned int>(produtosRecomendacao[i], frequenciaProduto));
		}
	}
}

void VendeMaisMais::preencheMapProdutoFrequenciaBottom10(vector<string> &produtosRecomendacaoPorOrdemFrequencia, vector<Cliente> &Bottom10)
{
	for (int i = 0; i < produtosRecomendacaoPorOrdemFrequencia.size(); i++)
	{
		unsigned int somatorio = 0;
		for (int j = 0; j < Bottom10.size(); j++)
		{
			unsigned int quantidade = quantasVezesComprou(Bottom10[j].getId(), produtosRecomendacaoPorOrdemFrequencia[i]);
			somatorio = somatorio + quantidade;
		}
		produtoRecomendacaoFrequenciaBottom10x.insert(pair<string, unsigned int>(produtosRecomendacaoPorOrdemFrequencia[i], somatorio));
	}
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
			size_t index1 = line.find_first_of(';');
			size_t index2 = (line.substr(index1 + 1)).find_first_of(';') + (line.substr(0, index1 + 1)).length();
			size_t index3 = line.find_last_of(';');
			unsigned int id = stoi(line.substr(0, index1 - 1));
			string name = line.substr(index1 + 2, (index2 - 1) - (index1 + 2));
			Data date = Data(line.substr(index2 + 2, (index3 - 1) - (index2 + 2)));
			float value = stof(line.substr(index3 + 2));
			Cliente c = Cliente(id, name, date, value);
			clientes.push_back(c);
			lineCount++;
		}
		else
		{
			lineCount++;
		}
	}
}

// lista os clientes por ordem alfabetica crescente
void VendeMaisMais::listarClientesOrdemAlfa() const
{
	vector<Cliente> vec = clientes;
	sort(vec.begin(), vec.end());
	cout << setw(5) << left << "ID" << setw(25) << left << "Nome" << setw(12) << left << "Data" << setw(6) << left << "Montante" << endl;
	cout << "--------------------------------------------------" << endl;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << endl;
	}
}

// mostra a informacao individual de um cliente
void VendeMaisMais::mostraInformacaoCliente(string nome) const
{
	bool flag = false;
	for (unsigned int i = 0; i < clientes.size(); i++)
	{
		if (clientes[i].getNome() == nome)
		{
			flag = true;
		}
	}
	if (flag == false)
	{
		cout << "Nenhum cliente foi encontrado com este nome" << endl;
	}
	if (flag == true)
	{
		cout << setw(5) << left << "ID" << setw(25) << left << "Nome" << setw(12) << left << "Data" << setw(6) << left << "Montante" << endl;
		cout << "--------------------------------------------------" << endl;
		for (unsigned int i = 0; i < clientes.size(); i++)
		{
			if (clientes[i].getNome() == nome)
			{
				cout << clientes[i] << endl;
			}
		}
	}
}

void VendeMaisMais::mostraInformacaoTodosClientes() const
{
	cout << setw(5) << left << "ID" << setw(25) << left << "Nome" << setw(12) << left << "Data" << setw(6) << left << "Montante" << endl;
	cout << "--------------------------------------------------" << endl;
	for (unsigned int i = 0; i < clientes.size(); i++)
	{
		cout << clientes[i] << endl;
	}
}

void VendeMaisMais::criarCliente(unsigned int id, string nome, Data cartaoCliente, float volCompras)
{
	Cliente c = Cliente(id, nome, cartaoCliente, volCompras);
	clientes.push_back(c);
	cout << "O cliente foi adicionado com sucesso" << endl;
}

void VendeMaisMais::editarCliente(unsigned int idCheck, unsigned int id, string nome, float volCompras, Data cartaoCliente)
{
	bool flag = false;
	for (unsigned int i = 0; i < clientes.size(); i++)
	{
		if (clientes[i].getId() == idCheck)
		{
			flag = true;
			clientes[i].setId(id);
			clientes[i].setNome(nome);
			clientes[i].setcartaoCliente(cartaoCliente);
			clientes[i].setVolCompras(volCompras);
			cout << "O cliente foi editado com sucesso" << endl;
		}
	}
	if (flag == false)
	{
		cout << "Nenhum cliente foi encontrado com este ID" << endl;
	}
}

void VendeMaisMais::removerCliente(string nome)
{
	bool flag = false;
	for (unsigned int i = 0; i < clientes.size(); i++)
	{
		if (clientes[i].getNome() == nome)
		{
			flag = true;
			clientes.erase(clientes.begin() + i);
			cout << "O cliente foi removido com sucesso" << endl;
		}
	}
	if (flag == false)
	{
		cout << "Nenhum cliente foi encontrado com este nome" << endl;
	}
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
			size_t index1 = line.find_first_of(';');
			string nome = line.substr(0, index1 - 1);
			float custo = stof(line.substr(index1 + 2));
			Produto p = Produto(nome, custo);
			produtos.push_back(p);
			lineCount++;
		}
		else
		{
			lineCount++;
		}
	}
}

void VendeMaisMais::listarProdutos() const
{
	vector<Produto> vec = produtos;
	sort(vec.begin(), vec.end());
	cout << setw(25) << left << "Produtos" << "Custo" << endl;
	cout << "------------------------------" << endl;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << endl;
	}
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
			size_t index1 = line.find_first_of(';');
			size_t index2 = line.find_last_of(';');
			unsigned int id = stoi(line.substr(0, index1 - 1));
			Data date = Data(line.substr(index1 + 2, (index2 - 1) - (index1 + 2)));
			string stringProdutos = line.substr(index2 + 2);
			vector<string> vetor;
			extractProducts(vetor, stringProdutos, 0, (count(stringProdutos.begin(), stringProdutos.end(), ',')));
			Transacao t = Transacao(id, date, vetor);
			transacoes.push_back(t);
			lineCount++;
		}
		else
		{
			lineCount++;
		}
	}
}

void VendeMaisMais::mostrarTransacoesDataEspecifica(Data data) const {

	while (!verifyDate(data.getDia(), data.getMes(), data.getAno()))
	{
		cout << "A data que introduziu e invalida!" << endl;
		cout << "Introduza novamente: ";
		cout << endl;
		data = IntroduzaData();
	}

	int transacoesMostradas = 0; //Numero de transacoes mostradas no ecra

	cout << "Transacoes do dia " << data << endl << endl;
	cout << "ID   Produtos Comprados" << endl;
	cout << "-----------------------" << endl;

	for (int i = 0; i < transacoes.size(); i++)
	{
		if (transacoes[i].getData() == data)
		{
			cout << setw(5) << left << transacoes[i].getIdCliente() << setw(50) << left << transacoes[i].getProdutos() << endl;
			transacoesMostradas++;
		}
	}
	cout << endl;

	if (transacoesMostradas == 0)
	{
		cout << "Lamentamos mas nao foram encontradas quaisquer transacoes na data introduzida!" << endl << endl;
	}

}

void VendeMaisMais::mostrarTransacoesEntreDatas(Data dataAntiga, Data dataRecente) const { //A dataAntiga é mais antiga do que a dataRecente

	/*
	while (!verifyDate(dataAntiga.getDia(), dataAntiga.getMes(), dataAntiga.getAno()))
	{
		cout << "A data mais antiga que introduziu e invalida!" << endl;
		cout << "Introduza novamente: ";
		dataAntiga = IntroduzaData();
	}

	while (!verifyDate(dataRecente.getDia(), dataRecente.getMes(), dataRecente.getAno()))
	{
		cout << "A data mais recente que introduziu e invalida!" << endl;
		cout << "Introduza novamente: ";
		dataRecente = IntroduzaData();
	}
	*/

	int transacoesMostradas = 0;//Numero de transacoes mostradas no ecra
	//while
	
	while(!verifyDatesOrder(dataAntiga.getDia(), dataAntiga.getMes(), dataAntiga.getAno(), dataRecente.getDia(), dataRecente.getMes(), dataRecente.getAno()))
	{
		
		cout << "As datas que introduziu encontram-se trocadas cronologicamente!" << endl;
		cout << "Introduza novamente a data mais antiga: ";
		cout << endl;
		dataAntiga = IntroduzaData();
		cout << "Introduza novamente a data mais recente: ";
		cout << endl;
		dataRecente = IntroduzaData();
		
		//mostrarTransacoesEntreDatas(d1, d2); //Chama a funcao novamente para verificar se as novas datas introduzidas sao validas
	}

		cout << "Transacoes desde " << dataAntiga << " ate " << dataRecente << endl << endl;
		cout << "ID   Produtos Comprados" << endl;
		cout << "-----------------------" << endl;

		for (int i = 0; i < transacoes.size(); i++)
		{
			if (!((transacoes[i].getData().getAno() >= dataAntiga.getAno()) && (transacoes[i].getData().getAno() <= dataRecente.getAno())))//se o ano de uma transacao é mais antigo do que o ano da data antiga OU é mais recente do que o ano da data recente, entao certamente NAO estara entre as duas datas
			{
			}
			else if ((transacoes[i].getData().getAno() > dataAntiga.getAno()) && (transacoes[i].getData().getAno() < dataRecente.getAno())) // se o ano de uma transacao é mais recente do que o ano da data antiga E é mais antigo do que o ano da data recente, entao certamente ESTARA entre as duas datas
			{
				cout << setw(5) << left << transacoes[i].getIdCliente() << setw(50) << left << transacoes[i].getProdutos() << endl;
				transacoesMostradas++;
			}
			else if (!((transacoes[i].getData().getMes() >= dataAntiga.getMes()) && (transacoes[i].getData().getMes() <= dataRecente.getMes()))) //Depois do que ja foi verificado se o mes de uma transacao é menor do que o mes da data antiga OU é maior do que o mes da data recente, entao certamente NAO estara entre as duas datas
			{
			}
			else if ((transacoes[i].getData().getMes() > dataAntiga.getMes()) && (transacoes[i].getData().getMes() < dataRecente.getMes())) //Depois do que ja foi verificado se o mes de uma transacao é maior do que o mes da data antiga E é menor do que o mes da data recente, entao certamente ESTARA entre as duas datas
			{
				cout << setw(5) << left << transacoes[i].getIdCliente() << setw(50) << left << transacoes[i].getProdutos() << endl;
				transacoesMostradas++;
			}
			else if ((transacoes[i].getData().getDia() >= dataAntiga.getDia()) && (transacoes[i].getData().getDia() <= dataRecente.getDia())) //Depois do que ja foi verificado se o dia de uma transacao é maior ou igual ao o mes da data antiga E é menor ou igual ao mes da data recente, entao certamente ESTARA entre as duas datas CASO CONTRARIO NAO ESTARA
			{
				cout << setw(5) << left << transacoes[i].getIdCliente() << setw(50) << left << transacoes[i].getProdutos() << endl;
				transacoesMostradas++;
			}
		}
		cout << endl;

	if (transacoesMostradas == 0)
		cout << "Lamentamos mas nao foram encontradas quaisquer transacoes entre as datas introduzidas!" << endl;
}

void VendeMaisMais::adicionarTransacao(unsigned int id, Data d, string listaProdutos)
{
	vector<string> prod;
	string lista;
	unsigned int numVirgulas = count(listaProdutos.begin(), listaProdutos.end(), ',');
	extractProducts(prod, listaProdutos, 0, numVirgulas);
	float somatorio = 0;
	bool flag = true;
	for (int i = 0; i < prod.size(); i++)
	{
		if (!verifyProduct(prod[i], produtos))
		{
			flag = false;
		}
	}
	if (flag == false)
	{
		cout << "Lamentamos. Pelo menos um dos produtos inseridos nao existe!" << endl;
		cout << "Insira outra lista de produtos: ";
		getline(cin, lista);
		adicionarTransacao(id, d, lista);
	}
	else
	{
		for (int i = 0; i < prod.size(); i++)
		{
			for (int j = 0; j < produtos.size(); j++)
			{
				if (prod[i] == produtos[j].getNome())
				{
					somatorio = somatorio + produtos[j].getCusto();
				}
			}
		}
		for (int i = 0; i < clientes.size(); i++)
		{
			if (id == clientes[i].getId())
			{
				somatorio = clientes[i].getVolCompras() + somatorio;
				clientes[i].setVolCompras(somatorio);
			}
		}
		Transacao t = Transacao(id, d, prod);
		transacoes.push_back(t);
		cout << "A transacao foi adicionada com sucesso" << endl;
		cout << "O montante gasto por este cliente foi atualizado!" << endl;
	}
}

void VendeMaisMais::mostraTransacoesCliente(string nome) const
{
	bool flag = false;
	unsigned int id;
	for (unsigned int i = 0; i < clientes.size(); i++)
	{
		if (clientes[i].getNome() == nome)
		{
			flag = true;
			id = clientes[i].getId();
		}
	}
	if (flag == false)
	{
		cout << "Nenhum cliente foi encontrado com este nome" << endl;
	}
	if (flag == true)
	{
		bool flag2 = false;
		for (unsigned int i = 0; i < transacoes.size(); i++)
		{
			if (transacoes[i].getIdCliente() == id)
			{
				flag2 = true;
			}
		}
		if (flag == false)
		{
			cout << "Nenhuma transacao foi encontrada para o cliente que especificou" << endl;
		}
		if (flag2 == true)
		{
			vector<Transacao> vec;
			for (unsigned int i = 0; i < transacoes.size(); i++)
			{
				if (transacoes[i].getIdCliente() == id)
				{
					Transacao t = transacoes[i];
					vec.push_back(t);
				}
			}
			sort(vec.begin(), vec.end(), transacaoCrono);//ordena as transacoes do cliente por ordem cronologica
			cout << setw(5) << left << "ID" << setw(12) << left << "Data" << "Produtos" << endl;
			cout << "-----------------------------------------------" << endl;
			for (unsigned int i = 0; i < vec.size(); i++)
			{
				cout << vec[i] << endl;
			}
		}
	}
}

void VendeMaisMais::mostraTodasTransacoes() const
{
	cout << setw(5) << left << "ID" << setw(12) << left << "Data" << "Produtos" << endl;
	cout << "-----------------------------------------------" << endl;
	for (unsigned int i = 0; i < transacoes.size(); i++)
	{
		cout << transacoes[i] << endl;
	}
}

/*********************************
* Recomendacoes
********************************/

void VendeMaisMais::recomendarCliente()
{
	/*MATRIX CREATION------------------------------------------------------------------------------------------------------------*/
	vector<vector<bool>> matrix;

	for (int i = 0; i < clientes.size(); i++)
	{
		vector<bool>productsLine;

		for (int j = 0; j < produtos.size(); j++)
		{
			productsLine.push_back(checkProduct(clientes[i].getId(), produtos[j].getNome(), transacoes));
		}
		matrix.push_back(productsLine);
	}
	/*-----------------------------------------------------------------------------------------------------------------------------*/
	unsigned int id;

	cout << "Introduza o ID do cliente alvo" << endl << endl;
	cout << "ID: ";
	cin >> id;//ID of the advertised client
	while (cin.fail() || id < 0)
	{
		cin.ignore();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Tente novamente: ";
		cin >> id;
	}

	vector<string> advertismentVector;//Candidate Products

	int advertisedPosition;//Matrix line position of the advertised client(it corresponds to his position on the clients vector)

	advertisedPosition = clientVectorPosition(id, clientes); // position the advertised client occupies on both clients' vector and matrix(they are both the same)

	while (advertisedPosition == 1000)
	{
		cout << "Nao exite um cliente com este ID" << endl;
		cout << "Introduza outro ID: ";
		cin >> id;
		advertisedPosition = clientVectorPosition(id, clientes);
	}

	for (int i = 0; i < clientes.size(); i++)//We will run through the matrix vector(it has the same number of lines has the clients lines)
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
				else if (matrix.at(i).at(j) == true && !matrix.at(advertisedPosition).at(j))//if a client has a product that the advertised one doesn't, then we will increase one on the nonCommonProducts variable
				{
					nonCommonProducts++;
				}
			}

			//I will consider similar shopping habbits, if two people have bought at least 2 items in common

			if (commonProducts >= 2 && nonCommonProducts > 0)//if a client has bought at least the same 2 items has the advertised one, and has also bought something that the advertised one didnt, then the items bought by the given client but not the advertised one will go into the advertisment vector
			{
				for (int j = 0; j < matrix.at(i).size(); j++)
				{
					if (matrix.at(i).at(j) == true && !matrix.at(advertisedPosition).at(j))//the products that a given client has but the advertised one doesn't are put in a list
					{
						advertismentVector.push_back(produtos[j].getNome());
					}

				}
			}
		}

	}
	if (advertismentVector.size() == 0)
	{
		cout << "Nao foi possivel recomendar nenhum produto" << endl;
	}
	else
	{
		string produtoPublicitado = mostFrequentName(advertismentVector);
		cout << "Ja experimentou " << produtoPublicitado << "?" << endl;
		cout << "Aproveite agora por apenas " << precoProduto(produtoPublicitado, produtos) << " euros!" << endl;
	}
}

void VendeMaisMais::verBottom10()
{
	vector<Cliente> vec = clientes;
	sort(vec.begin(), vec.end(), clienteMontante);
	cout << setw(5) << left << "ID" << setw(25) << left << "Nome" << setw(12) << left << "Data" << setw(6) << left << "Montante" << endl;
	cout << "--------------------------------------------------" << endl;
	for (int i = 0; (i < 10) && (i < vec.size()); i++)
	{
		cout << vec[i] << endl;
	}
}

void VendeMaisMais::recomendarBottom10()
{
	vector<Cliente> vec = clientes;
	vector<Cliente> bottom10;
	sort(vec.begin(), vec.end(), clienteMontante);
	for (int i = 0; (i < 10) && (i < vec.size()); i++)
	{
		bottom10.push_back(vec[i]);
	}

	vector<vector<bool>> matrix;

	for (int i = 0; i < bottom10.size(); i++)
	{
		vector<bool>productsLine;

		for (int j = 0; j < produtos.size(); j++)
		{
			productsLine.push_back(checkProduct(bottom10[i].getId(), produtos[j].getNome(), transacoes));
		}
		matrix.push_back(productsLine);
	}
	vector<string> produtosComunsBottom10;
	for (int j = 0; j < produtos.size(); j++)
	{
		bool productFlag = true;
		for (int i = 0; i < bottom10.size(); i++)
		{
			if (matrix[i][j] == false)
			{
				productFlag = false; // USAR UM FICHEIRO EM QUE EXISTA UM PRODUTO COMUM AOS BOTTOM 10
			}
		}
		if (productFlag == true)
		{
			produtosComunsBottom10.push_back(produtos[j].getNome());
		}
	}
	vector<Cliente> vetor = clientes;
	vector<Cliente> clientesNotBottom10;
	sort(vetor.begin(), vetor.end(), clienteMontanteInvertido);
	if (!(clientes.size() > 10))
	{
		cout << "Nao foi possivel efetuar uma recomendacao dado que nao ha mais de 10 clientes." << endl;
	}
	else
	{
		for (int i = 0; i < vetor.size() - 10; i++)
		{
			clientesNotBottom10.push_back(vetor[i]);
		}

		vector<vector<bool>> matrixNotBottom10;

		for (int i = 0; i < clientesNotBottom10.size(); i++)
		{
			vector<bool>productsLine;

			for (int j = 0; j < produtosComunsBottom10.size(); j++)
			{
				productsLine.push_back(checkProduct(clientesNotBottom10[i].getId(), produtosComunsBottom10[j], transacoes));
			}
			for (int k = 0; k < produtos.size(); k++)
			{
				if (!verifyProduct(produtos[k].getNome(), produtosComunsBottom10))
				{
					productsLine.push_back(checkProduct(clientesNotBottom10[i].getId(), produtos[k].getNome(), transacoes));
				}
			}
			matrixNotBottom10.push_back(productsLine);
		}
		vector<Cliente> clientesRecomendacao;
		for (int i = 0; i < clientesNotBottom10.size(); i++)
		{
			bool flag = true;
			for (int j = 0; j < produtosComunsBottom10.size(); j++)
			{
				if (matrixNotBottom10[i][j] == false)
				{
					flag = false;
				}
			}
			if (flag == true)
			{
				bool flag2 = false;
				for (int j = produtosComunsBottom10.size(); j < produtos.size(); j++)
				{
					if (matrixNotBottom10[i][j] == true)
					{
						flag = true;
					}
				}
				if (flag == true)
				{
					clientesRecomendacao.push_back(clientesNotBottom10[i]);
				}
			}
		}
		if (clientesRecomendacao.size() != 0)
		{
			vector<string> produtosRecomendacao;
			preencheMapClienteProd();
			for (int i = 0; i < clientesRecomendacao.size(); i++)
			{
				for (int j = 0; j < clienteProdx.at(clientesRecomendacao[i].getId()).size(); j++)
				{
					if (!verifyProduct(clienteProdx.at(clientesRecomendacao[i].getId())[j], produtosComunsBottom10))
					{
						produtosRecomendacao.push_back(clienteProdx.at(clientesRecomendacao[i].getId())[j]);
					}
				}
			}
			preencheMapProdutoRecomendacaoFrequencia(produtosRecomendacao);

			vector<string> produtosRecomendacaoSemRepetidos;

			for (map<string, unsigned int>::iterator it = produtoRecomendacaoFrequenciax.begin(); it != produtoRecomendacaoFrequenciax.end(); ++it)
			{
				produtosRecomendacaoSemRepetidos.push_back(it->first);
			}

			vector<string> produtosRecomendacaoPorOrdemFrequencia = produtosRecomendacaoSemRepetidos;
			sort(produtosRecomendacaoPorOrdemFrequencia.begin(), produtosRecomendacaoPorOrdemFrequencia.end(), comparaProdutoFreq);
			string produtoPublicitado;
			bool flag = false;
			preencheMapProdutoFrequenciaBottom10(produtosRecomendacaoPorOrdemFrequencia, bottom10);
			for (int i = 0; i < produtosRecomendacaoPorOrdemFrequencia.size(); i++)
			{
				if (produtoRecomendacaoFrequenciaBottom10x.at(produtosRecomendacaoPorOrdemFrequencia[i]) == 0)
				{
					flag = true;
					produtoPublicitado = produtosRecomendacaoPorOrdemFrequencia[i];
					break;
				}
			}
			if (flag == false)
			{
				unsigned int min = produtoRecomendacaoFrequenciaBottom10x.at(produtosRecomendacaoPorOrdemFrequencia[0]);
				for (int i = 1; i < produtosRecomendacaoPorOrdemFrequencia.size(); i++)
				{
					if ((produtoRecomendacaoFrequenciaBottom10x.at(produtosRecomendacaoPorOrdemFrequencia[i])) < min)
					{
						min = produtoRecomendacaoFrequenciaBottom10x.at(produtosRecomendacaoPorOrdemFrequencia[i]);
						produtoPublicitado = produtosRecomendacaoPorOrdemFrequencia[i];
					}
				}
			}


			cout << "Para os clientes mais distraidos..." << endl;
			cout << "Ja experimentou " << produtoPublicitado << "?" << endl;
			cout << "Aproveite agora por uns ridiculos " << precoProduto(produtoPublicitado, produtos) << " euros!!!" << endl;



		}
		else
		{
			cout << "Nao foi possivel efetuar uma boa recomendacao" << endl;//nao ha dados sufecientes (clientesRecomendacao vazio)
		}
	}
}

bool comparaProdutoFreq(string &p1, string &p2)
{
	if (produtoRecomendacaoFrequenciax.at(p2) < produtoRecomendacaoFrequenciax.at(p1))
	{
		return true;
	}
	else
	{
		return false;
	}
}

unsigned int VendeMaisMais::quantasVezesComprou(unsigned int idCliente, string produto)
{
	unsigned int somatorio = 0;
	for (int i = 0; i < clienteProdx.at(idCliente).size(); i++)
	{
		if (clienteProdx.at(idCliente)[i] == produto)
		{
			somatorio++;
		}
	}
	return somatorio;
}

/*********************************
 * Preservar Informacao
 ********************************/

 // guarda apenas a informacao de clientes e/ou de transacoes que foi alterada
void VendeMaisMais::saveChanges() {
	string fichClientes = this->fichClientes;
	//guradar informacao no ficheiro de clientes	
	ofstream clientesStream;
	string temporary;
	clientesStream.open(fichClientes);
	clientesStream << clientes.size() << endl;

	for (int i = 0; i < clientes.size(); i++)
	{
		if (i != 0)
		{
			temporary.append("\n");
		}
		temporary.append(to_string(clientes[i].getId()));
		temporary.append(" ; ");
		temporary.append(clientes[i].getNome());
		temporary.append(" ; ");
		temporary.append(to_string(clientes[i].getcartaoCliente().getDia()));
		temporary.append("/");
		temporary.append(to_string(clientes[i].getcartaoCliente().getMes()));
		temporary.append("/");
		temporary.append(to_string(clientes[i].getcartaoCliente().getAno()));
		temporary.append(" ; ");
		clientesStream << temporary;
		clientesStream << fixed << setprecision(2) << clientes[i].getVolCompras();
		clientesStream.unsetf(ios_base::floatfield);
		temporary.erase();
	}
	clientesStream.close();

	//guardar informacao no ficheiro de transacoes

	string fichTransacoes = this->fichTransacoes;
	ofstream transacoesStream;
	string temporary2;
	transacoesStream.open(fichTransacoes);
	transacoesStream << transacoes.size() << endl;

	for (int i = 0; i < transacoes.size(); i++)
	{
		if (i != 0)
		{
			temporary2.append("\n");
		}
		temporary2.append(to_string(transacoes[i].getIdCliente()));
		temporary2.append(" ; ");
		temporary2.append(to_string(transacoes[i].getData().getDia()));
		temporary2.append("/");
		temporary2.append(to_string(transacoes[i].getData().getMes()));
		temporary2.append("/");
		temporary2.append(to_string(transacoes[i].getData().getAno()));
		temporary2.append(" ; ");
		temporary2.append(transacoes[i].getProdutos());
		transacoesStream << temporary2;
		temporary2.erase();
	}
	transacoesStream.close();

}

/*********************************
 * Mostrar Loja
 ********************************/

 // mostra o conteudo de uma loja
void VendeMaisMais::show()
{
	cout << "Numero de clientes: " << clientes.size() << endl;
	cout << "Numero de transacoes: " << transacoes.size() << endl;
	cout << "Stock de produtos: " << endl;
	cout << setw(25) << left << "Produtos" << "Custo" << endl;
	cout << "------------------------------" << endl;
	for (int i = 0; i < produtos.size(); i++)
	{
		cout << produtos[i] << endl;
	}
}


