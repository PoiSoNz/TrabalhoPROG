#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<vector>
#include<cmath>
#include<istream>
#include <sstream>
using namespace std;

//Clients' struct
struct client_t
{
	unsigned int clientID;
	string clientNAME;
	double clientSHOP;
};

//Transactions' struct
struct transaction_t
{
	unsigned int clientID;
	unsigned int transactionDAY;
	unsigned int transactionMONTH;
	unsigned int transactionYEAR;
	string transactionITEMS;
};

//Note: products don't require a struct

//All used functions
void checkFile(string fileName, ifstream &streamName);
void saveClients(vector<client_t>&clientsVector, ifstream &streamClients);
void saveTransactions(vector<transaction_t>&transactionsVector, ifstream &streamTransactions);
void saveProducts(vector<string>&productsVector, ifstream &streamProducts);

void trim(string &s);

void optionsMenu(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector);

void manageClientOption(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector);
void createClient(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector);
void modifyClient(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector);
void deleteClient(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector);

void addTransaction(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector);

void displayClientOption(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector);
void displaySpecificClient(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector);
void displayAllClients(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector);

void displayTransactionOption(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector);
void searchTransactionSpecificDay(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector);
void searchTransactionPeriod(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector);
void searchTransactionClient(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector);
void searchAllTransactions(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector);

void advertisment(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector);

void exitProgram(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector);

bool verifyDate(int day, int month, int year);
bool verifyDatesOrder(int oldDay, int oldMonth, int oldYear, int recentDay, int recentMonth, int recentYear);


bool checkProduct(unsigned int clientId, string product, vector<transaction_t>&transactionsVector);

int clientVectorPosition(unsigned int id, vector<client_t>&clientsVector);

bool confirmChoice();

void exitSaveClients(vector<client_t>&clientsVector);
void exitSaveTransactions(vector<transaction_t>&transactionsVector);

int main()
{
	//Save information kept on clients' file
	string clients; //Clients' file name
	ifstream streamClients;
	cout << "Introduce clients' file name: ";
	cin >> clients;
	streamClients.open(clients);
	checkFile(clients, streamClients);  //To ensure the user provides a valid clients' file

	vector<client_t> clientsVector; //Clients' vector
	saveClients(clientsVector, streamClients);//save information kept on clients' file


											  //Save information kept on transactions' file
	string transactions; //Transactions' file name
	ifstream streamTransactions;
	cout << "Introduce transactions' file name: ";
	cin >> transactions;
	streamTransactions.open(transactions);
	checkFile(transactions, streamTransactions);  //To ensure the user provides a valid transactions' file

	vector<transaction_t> transactionsVector; //Transactions' vector
	saveTransactions(transactionsVector, streamTransactions); //save information kept on transactions' file


															  //Save information kept on products' file
	string products; //Products' file name
	ifstream streamProducts;
	cout << "Introduce products' file name: ";
	cin >> products;
	streamProducts.open(products);
	checkFile(products, streamProducts);  //To ensure the user provides a valid products' file

	vector<string>productsVector;//Products' vector
	saveProducts(productsVector, streamProducts);//save information kept on products' file



												 //Display menu
	optionsMenu(clientsVector, transactionsVector, productsVector);//I use vectors as parameters because all the operations are functions invoked by the optionsMenu function, being this the only way for all operations to receive the vectors(clients, transactions and products). Otherwise i wouldnt be able to change the vectors content unless i had declared them as global








	return 0;
}
/*READ INFORMATION KEPT ON FILES----------------------------------------------------------------------------------------------------------------*/
void checkFile(string fileName, ifstream &streamName)  //Checks if a given file exists
{
	while (!streamName.is_open())
	{
		cout << "File " << fileName << " was not found" << endl;
		cout << "Please provide the right file: ";
		cin >> fileName;
		streamName.open(fileName);
	}
	cout << "File was successfuly read" << endl << endl;
}
void saveClients(vector<client_t>&clientsVector, ifstream &streamClients)
{
	string line; //Used to save each file's line
	string clientId; //Saves each line's client id
	string clientName; //Saves each line's client name
	string clientShop; //Saves each line's client amount spent on shop
	client_t c;

	while (getline(streamClients, line))
	{
		int firstSemicolon = line.find_first_of(";");
		int lastSemicolon = line.find_last_of(";");

		clientId = line.substr(0, firstSemicolon);
		clientName = line.substr(firstSemicolon + 1, lastSemicolon - (firstSemicolon + 1)); // lastSemicolon - (firstSemicolon + 1) corresponds to the numbers of elements between the first and second semicolon
		clientShop = line.substr(lastSemicolon + 1);

		c.clientID = stoi(clientId);
		trim(clientName);//To remove useless spaces on client name
		c.clientNAME = clientName;
		c.clientSHOP = stod(clientShop);

		clientsVector.push_back(c);
	}
}
void saveTransactions(vector<transaction_t>&transactionsVector, ifstream &streamTransactions)
{
	string line; //Used to save each file's line
	string clientId; //Saves each line's client id
	string transactionDay; //Saves each line's transaction day
	string transactionMonth; //Saves each line's transaction month
	string transactionYear; //Saves each line's transaction year
	string transactionItems;//Saves each line's transaction items
	transaction_t t;

	while (getline(streamTransactions, line))
	{
		int firstSemicolon = line.find_first_of(";");
		int secondSemicolon = line.find_last_of(";");
		int firstSlash = line.find_first_of("/"); //First date's slash positon
		int secondSlash = line.find_last_of("/"); //Second date's slash position

		clientId = line.substr(0, firstSemicolon);
		transactionDay = line.substr(firstSemicolon + 1, firstSlash - (firstSemicolon + 1)); // (firstSlash - (firstSemicolon + 1)) is the distance between the first semicolon and the first date's slash
		transactionMonth = line.substr(firstSlash + 1, secondSlash - (firstSlash + 1)); // (secondSlash - (firstSlash + 1)) is the distance between the first and second date's slash
		transactionYear = line.substr(secondSlash + 1, secondSemicolon - (secondSlash + 1)); //(secondSemicolon - (secondSlash + 1)) is the distance between the second date's slash and the second semicolon
		transactionItems = line.substr(secondSemicolon + 1);



		t.clientID = stoi(clientId);
		t.transactionDAY = stoi(transactionDay);
		t.transactionMONTH = stoi(transactionMonth);
		t.transactionYEAR = stoi(transactionYear);
		trim(transactionItems);//to remove useless spaces on the transanction's item list
		t.transactionITEMS = transactionItems;

		transactionsVector.push_back(t);
	}
}
void saveProducts(vector<string>&productsVector, ifstream &streamProducts)
{
	string line; //Used to save each file's line
	while (getline(streamProducts, line))
	{
		productsVector.push_back(line);
	}
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*TRIM---------------------------------------------------------------------------------------------------------------------------------------------*/
void trim(string &s)
{
	int firstSpace = s.find_first_of(" ");
	int lastSpace = s.find_last_of(" ");


	if (firstSpace == 0)
	{
		s.erase(0, 1);
		trim(s);
	}
	else if (lastSpace == (s.size() - 1))
	{
		s.erase(s.size() - 1, 1);
		trim(s);
	}

	for (int i = 0; i < s.size(); i++)
	{
		if (((int)s.at(i) == 32) && ((int)s.at(i + 1) == 32)) // Space's ascii code is 32
		{
			s.erase(i, 1);
		}
	}
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------*/

//MENUS

/*MAIN MENU----------------------------------------------------------------------------------------------------------------------------------------*/
void optionsMenu(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector)
{//Important note A: all the functions invoked by this optionsMenu function take the three vectors(clients, transactions and products) as parameters even if they dont work with them, because in the end all the functions call the optionsMenu funtion again
	unsigned int operation; //Selected operation's number
	cout << "Select the desired operation:" << endl;
	cout << "1. Manage clients" << endl;
	cout << "2. Add transaction" << endl;
	cout << "3. Display client information" << endl;
	cout << "4. Display transaction information" << endl;
	cout << "5. Advertisment" << endl;
	cout << "6. Exit" << endl;

	cout << "Chosen operation: ";
	cin >> operation;

	cout << endl;

	switch (operation)
	{
	case 1:
		manageClientOption(clientsVector, transactionsVector, productsVector);
	case 2:
		addTransaction(clientsVector, transactionsVector, productsVector);
	case 3:
		displayClientOption(clientsVector, transactionsVector, productsVector);
	case 4:
		displayTransactionOption(clientsVector, transactionsVector, productsVector);
	case 5:
		advertisment(clientsVector, transactionsVector, productsVector);
	case 6:
		exitProgram(clientsVector, transactionsVector);
	}


}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/

/*MENU OPTIONS THAT DEAL WITH CLIENTS MANAGMENT----------------------------------------------------------------------------------------------------------------------------------------*/
void manageClientOption(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector)
{
	unsigned int operation;
	cout << "Select the operation to perform on a client:" << endl;
	cout << "1. Create new client" << endl;
	cout << "2. Modify client" << endl;
	cout << "3. Delete client" << endl;
	cout << "4. Cancel" << endl;

	cout << "Chosen operation: ";
	cin >> operation;

	cout << endl;

	switch (operation)
	{
	case 1:
		createClient(clientsVector, transactionsVector, productsVector);
	case 2:
		modifyClient(clientsVector, transactionsVector, productsVector);
	case 3:
		deleteClient(clientsVector, transactionsVector, productsVector);
	case 4:
		optionsMenu(clientsVector, transactionsVector, productsVector);
	}

}

void createClient(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector)
{
	if (confirmChoice())
	{
		unsigned int clientId;
		string clientName;
		double clientShop;
		client_t c;

		cout << "Introduce the client details" << endl << endl;

		cout << "ID: ";
		cin >> clientId;

		cout << "Name: ";
		cin.ignore();
		getline(cin, clientName);
		trim(clientName);

		cout << "Amount spent: ";
		cin >> clientShop;

		c.clientID = clientId;
		c.clientNAME = clientName;
		c.clientSHOP = clientShop;

		clientsVector.push_back(c);

		cout << "Client has been successfuly created!" << endl << endl;
	}

	optionsMenu(clientsVector, transactionsVector, productsVector);
}
void modifyClient(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector)
{
	if (confirmChoice())
	{
		unsigned int IdToReplace;//ID that belongs to the client who will be modified

		unsigned int newId;//Modified ID
		string newName;//Modified name
		double newShop;//Modified shop amount

		cout << "Introduce the ID whose client you want to modify" << endl << endl;
		cout << "ID: ";
		cin >> IdToReplace;


		for (int i = 0; i < clientsVector.size(); i++)
		{
			if (clientsVector.at(i).clientID == IdToReplace)// if it finds the client with the providen id to replace, that client is erased and a new one will be added with the new information. The practical use will be a replace.
			{//If the client is found the user will be asked for the modifications
				cout << endl;
				cout << "Introduce the new client details that will replace the previous" << endl << endl;

				cout << "New ID: ";
				cin >> newId;

				cout << "New name: ";
				cin.ignore();
				getline(cin, newName);
				trim(newName);

				cout << "New spent amount: ";
				cin >> newShop;

				clientsVector.at(i).clientID = newId;     //ID modification
				clientsVector.at(i).clientNAME = newName;//name modification
				clientsVector.at(i).clientSHOP = newShop; //amount spent modification

				cout << "Client has been successfuly modified!" << endl << endl;
				optionsMenu(clientsVector, transactionsVector, productsVector);
			}
		}
		//If the "for" loop ends it means that no client was found with such id, so the user will be asked if he wants to modify a diferent client or quit to main menu
		unsigned int operation;

		cout << "No client was found with such id!" << endl << endl;

		cout << "Do you wish to modify a different client" << endl;
		cout << "1. Yes, modify a different client" << endl;
		cout << "2. No, return to main menu" << endl;
		cout << "Chosen operation: ";
		cin >> operation;

		cout << endl;

		switch (operation)
		{
		case 1:
			modifyClient(clientsVector, transactionsVector, productsVector);
		case 2:
			optionsMenu(clientsVector, transactionsVector, productsVector);
		}
	}
	optionsMenu(clientsVector, transactionsVector, productsVector);
}
void deleteClient(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector)
{
	if (confirmChoice())
	{
		unsigned int clientId;

		cout << "Introduce the ID whose client you want to delete" << endl << endl;
		cout << "ID: ";
		cin >> clientId;

		for (int i = 0; i < clientsVector.size(); i++)
		{
			if (clientsVector.at(i).clientID == clientId) //If an element from the clients vector has the same id as the introduced, it will be erased
			{
				clientsVector.erase(clientsVector.begin() + i);
				cout << "Client has been successfuly deleted!" << endl << endl;
				optionsMenu(clientsVector, transactionsVector, productsVector);
			}

		}

		//If the "for" loop ends it means that there was no id match, so the user will be informed and will ask the user if he wants to reintroduce a new id to search or just quit to main menu
		unsigned int operation;

		cout << "No client was found with such id!" << endl << endl;

		cout << "Do you wish to re-enter a new id?" << endl;
		cout << "1. Yes, introduce new id" << endl;
		cout << "2. No, return to main menu" << endl;
		cout << "Chosen operation: ";
		cin >> operation;

		cout << endl;

		switch (operation)
		{
		case 1:
			deleteClient(clientsVector, transactionsVector, productsVector);
		case 2:
			optionsMenu(clientsVector, transactionsVector, productsVector);
		}
	}
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*MENU OPTION THAT ADDS A TRANSACTION----------------------------------------------------------------------------------------------------------------------------------------*/
void addTransaction(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector)
{
	if (confirmChoice())
	{
		unsigned int clientId;
		string transactionDate;//Saves the date as dd/mm/yyyy format
		int transactionDay;
		int transactionMonth;
		int transactionYear;
		string transactionItems;

		transaction_t t;

		cout << "Provide the required transaction information" << endl;

		cout << "Client id: ";
		cin >> clientId;

		//Check if id exists
		bool IdExists=false;
		for (int i = 0; i < clientsVector.size(); i++)
		{
			if (clientsVector.at(i).clientID == clientId)
				IdExists = true;
		}

		if (!IdExists)
		{
			unsigned int operation;
			cout << "The introduced id does not exist!" << endl << endl;
			cout << "Select the desired operation:" << endl;
			cout << "1. Re-introduce a transaction" << endl;
			cout << "2. Quit to main menu" << endl;
			cout << "Chosen operation: ";
			cin >> operation;

			switch (operation)
			{
			case 1:
				addTransaction(clientsVector, transactionsVector, productsVector);
			case 2:
				optionsMenu(clientsVector, transactionsVector, productsVector);
			}
		}

		cout << "Transaction date (dd/mm/yyyy) : ";
		cin >> transactionDate;

		int firstSlash = transactionDate.find_first_of("/");
		int secondSlash = transactionDate.find_last_of("/");

		transactionDay = stoi(transactionDate.substr(0, firstSlash));
		transactionMonth = stoi(transactionDate.substr(firstSlash + 1, secondSlash - (firstSlash + 1)));
		transactionYear = stoi(transactionDate.substr(secondSlash + 1));

		if (!verifyDate(transactionDay, transactionMonth, transactionYear))//Verifies if the date is valid
		{
			unsigned int operation;
			cout << "Select the desired operation:"<<endl;
			cout << "1. Re-introduce a transaction" << endl;
			cout << "2. Quit to main menu" << endl;
			cout << "Chosen operation: ";
			cin >> operation;

			switch (operation)
			{
			case 1:
				addTransaction(clientsVector, transactionsVector, productsVector);
			case 2:
				optionsMenu(clientsVector, transactionsVector, productsVector);
			}
		}


		cout << "Transaction items (item, item,...) : ";
		cin.ignore();
		getline(cin, transactionItems);
		trim(transactionItems);

		

		t.clientID = clientId;
		t.transactionDAY = transactionDay;
		t.transactionMONTH = transactionMonth;
		t.transactionYEAR = transactionYear;
		t.transactionITEMS = transactionItems;
		transactionsVector.push_back(t);

		cout << "Transaction has been successfuly added!" << endl << endl;

	}
	optionsMenu(clientsVector, transactionsVector, productsVector);
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*MENU OPTIONS THAT DISPLAY CLIENT INFORMATION----------------------------------------------------------------------------------------------------------------------------------------*/
void displayClientOption(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector)
{
	unsigned int operation;

	cout << "Select what you would like to view:" << endl;
	cout << "1. Display information about a specific client" << endl;
	cout << "2. Display all clients information" << endl;
	cout << "3.Cancel" << endl;
	cout << "Chosen option: ";
	cin >> operation;

	cout << endl;

	switch (operation)
	{
	case 1:
		displaySpecificClient(clientsVector, transactionsVector, productsVector);
	case 2:
		displayAllClients(clientsVector, transactionsVector, productsVector);
	case 3:
		optionsMenu(clientsVector, transactionsVector, productsVector);
	}

}

void displaySpecificClient(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector)
{
	unsigned int clientId;

	cout << "Introduce the ID whose client you want to view" << endl << endl;
	cout << "ID: ";
	cin >> clientId;

	for (int i = 0; i < clientsVector.size(); i++)
	{
		if (clientId == clientsVector.at(i).clientID) //if the provided client id is found on clients vector it shows the information kept on that vector position, after that the main menu is shown
		{
			cout << "Client name: ";
			cout << clientsVector.at(i).clientNAME << endl;

			cout << "Amount spent: ";
			cout << setprecision(2) << fixed << clientsVector.at(i).clientSHOP << endl << endl;

			optionsMenu(clientsVector, transactionsVector, productsVector);
		}

	}

	//If the "for" loop ends it means that no client was found with such id, so it will be saked to the user if he wants to go to main menu or re-enter a new id

	unsigned int operation;//The provided id was not found, "operation" decides if the user provides a new id or goes back to main menu
	cout << "No client was found with such id!" << endl << endl;

	cout << "Do you wish to re-enter a new id?" << endl;
	cout << "1. Yes, introduce new id" << endl;
	cout << "2. No, return to main menu" << endl;
	cout << "Chosen operation: ";
	cin >> operation;

	cout << endl;

	switch (operation)
	{
	case 1:
		displaySpecificClient(clientsVector, transactionsVector, productsVector);
	case 2:
		optionsMenu(clientsVector, transactionsVector, productsVector);
	}
}
void displayAllClients(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector)
{
	cout << "ID   NAME                AMOUNT SPENT" << endl; // 
	cout << "-------------------------------------" << endl;//Just to make the table look better

	for (int i = 0; i < clientsVector.size(); i++)
	{

		cout << setw(5) << left << clientsVector.at(i).clientID; //5 spaces are reserved to the client ID (the ID is writen starting from left to write)
		cout << setw(20) << left << clientsVector.at(i).clientNAME; //20 spaces are reserved to the client ID (the ID is writen starting from left to write)
		cout << setprecision(2) << fixed << clientsVector.at(i).clientSHOP << endl;//as the amount spent is the last to be displayed, it has no space restriction
	}

	cout << endl;//Leave a line gap between the next text that is displayed(just a matter of visual organization)
	optionsMenu(clientsVector, transactionsVector, productsVector);
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*MENU OPTIONS THAT DISPLAY TRANSACTIONS----------------------------------------------------------------------------------------------------------------------*/
void displayTransactionOption(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector)
{
	unsigned int operation;

	cout << "Select how do you want to search for transactions:" << endl;
	cout << "1. Search for a specific day" << endl;
	cout << "2. Search between two dates" << endl;
	cout << "3. Search for a client's transactions" << endl;
	cout << "4. Display all transactions" << endl;
	cout << "5. Cancel" << endl;
	cout << "Chosen operation: ";
	cin >> operation;

	cout << endl;

	switch (operation)
	{
	case 1:
		searchTransactionSpecificDay(clientsVector, transactionsVector, productsVector);
	case 2:
		searchTransactionPeriod(clientsVector, transactionsVector, productsVector);
	case 3:
		searchTransactionClient(clientsVector, transactionsVector, productsVector);
	case 4:
		searchAllTransactions(clientsVector, transactionsVector, productsVector);
	case 5:
		optionsMenu(clientsVector, transactionsVector, productsVector);

	}

}

void searchTransactionSpecificDay(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector)
{//Searches for a transaction on a given day
	string date;

	unsigned int transactionDay;
	unsigned int transactionMonth;
	unsigned int transactionYear;

	int numberOfTransactionsViewed=0;

	cout << "Introduce the day transaction date you want to search for:" << endl << endl;
	cout << "Transaction date (dd/mm/yyyy): ";
	cin >> date;

	int firstDateSlash = date.find_first_of("/");
	int secondDateSlash = date.find_last_of("/");

	transactionDay = stoi(date.substr(0, firstDateSlash));
	transactionMonth = stoi(date.substr(firstDateSlash + 1, secondDateSlash - (firstDateSlash + 1)));
	transactionYear = stoi(date.substr(secondDateSlash + 1));

	if (!verifyDate(transactionDay, transactionMonth, transactionYear))
		searchTransactionSpecificDay(clientsVector, transactionsVector, productsVector);

	for (int i = 0; i < transactionsVector.size(); i++)
	{
		if (transactionsVector.at(i).transactionDAY == transactionDay &&
			transactionsVector.at(i).transactionMONTH == transactionMonth &&
			transactionsVector.at(i).transactionYEAR == transactionYear)
		{
			cout << "ID: ";
			cout << transactionsVector.at(i).clientID << endl;

			cout << "Items bought: ";
			cout << transactionsVector.at(i).transactionITEMS << endl << endl;

			numberOfTransactionsViewed++;
		}
	}

	if (numberOfTransactionsViewed == 0)//Verifies if no transaction has been viewed. If that happened it will inform the user and ask if he wants to search for a new date
	{
		unsigned int operation;
		cout << "No transaction has been found in that day!" << endl << endl;
		cout << "What do you wish to do?" << endl;
		cout << "1. Search for another day" << endl;
		cout << "2. Quit to main menu" << endl;
		cout << "Chosen option: ";
		cin >> operation;

		cout << endl;

		switch (operation)
		{
		case 1:
			searchTransactionSpecificDay(clientsVector, transactionsVector, productsVector);
		case 2:
			optionsMenu(clientsVector, transactionsVector, productsVector);
		}
	}
	else
	{
		cout << "Transactions have been successfuly viewed!" << endl << endl;
		optionsMenu(clientsVector, transactionsVector, productsVector);
	}



}
void searchTransactionPeriod(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector)
{//Searches for transactions between two dates
	string date1;
	int day1;
	int month1;
	int year1;

	string date2;
	int day2;
	int month2;
	int year2;

	cout << "Introduce the dates to search for transactions (the first date must be previous to the second one):" << endl << endl;
	
	cout << "First date (dd/mm/yyyy): ";
	cin >> date1;
	
	int firstDate1Slash = date1.find_first_of("/");
	int secondDate1Slash = date1.find_last_of("/");

	day1 = stoi(date1.substr(0, firstDate1Slash));
	month1 = stoi(date1.substr(firstDate1Slash + 1, secondDate1Slash - (firstDate1Slash + 1)));
	year1 = stoi(date1.substr(secondDate1Slash + 1));
	
	if (!verifyDate(day1, month1, year1))
	{
		searchTransactionPeriod(clientsVector, transactionsVector, productsVector);
	}


	cout << "Second date (dd/mm/yyyy): ";
	cin >> date2;
	cout << endl;

	int firstDate2Slash = date2.find_first_of("/");
	int secondDate2Slash = date2.find_last_of("/");

	day2 = stoi(date2.substr(0, firstDate2Slash));
	month2 = stoi(date2.substr(firstDate2Slash + 1, secondDate2Slash - (firstDate2Slash + 1)));
	year2 = stoi(date2.substr(secondDate2Slash + 1));

	if (!verifyDate(day2, month2, year2))
	{
		searchTransactionPeriod(clientsVector, transactionsVector, productsVector);
	}


	if (!verifyDatesOrder(day1, month1, year1, day2, month2, year2))
	{
		searchTransactionPeriod(clientsVector, transactionsVector, productsVector);
	}

	int numberOfTransactionsViewed = 0;

	for (int i = 0; i < transactionsVector.size(); i++)
	{
		if (!((transactionsVector.at(i).transactionYEAR >= year1) && (transactionsVector.at(i).transactionYEAR <= year2)))//if a transaction year is not  greater year1 and less then year2 then its guaranteed to don't be bewtween the dates
		{
		}
		else if ((transactionsVector.at(i).transactionYEAR > year1) && (transactionsVector.at(i).transactionYEAR < year2))
		{
			numberOfTransactionsViewed++;

			cout << "ID: ";
			cout << transactionsVector.at(i).clientID << endl;

			cout << "Date: ";
			cout << transactionsVector.at(i).transactionDAY;
			cout << "/";
			cout << transactionsVector.at(i).transactionMONTH;
			cout << "/";
			cout << transactionsVector.at(i).transactionYEAR<<endl;

			cout << "Items: ";
			cout << transactionsVector.at(i).transactionITEMS << endl << endl;

		}
		else if (!((transactionsVector.at(i).transactionMONTH >= month1) && (transactionsVector.at(i).transactionMONTH <= month2)))
		{
		}
		else if ((transactionsVector.at(i).transactionMONTH > month1) && (transactionsVector.at(i).transactionMONTH < month2))
		{
			numberOfTransactionsViewed++;

			cout << "ID: ";
			cout << transactionsVector.at(i).clientID << endl;

			cout << "Date: ";
			cout << transactionsVector.at(i).transactionDAY;
			cout << "/";
			cout << transactionsVector.at(i).transactionMONTH;
			cout << "/";
			cout << transactionsVector.at(i).transactionYEAR << endl;

			cout << "Items: ";
			cout << transactionsVector.at(i).transactionITEMS << endl << endl;

		}
		else if ((transactionsVector.at(i).transactionDAY >= day1) && (transactionsVector.at(i).transactionDAY <= day2))
		{
			numberOfTransactionsViewed++;

			cout << "ID: ";
			cout << transactionsVector.at(i).clientID << endl;

			cout << "Date: ";
			cout << transactionsVector.at(i).transactionDAY;
			cout << "/";
			cout << transactionsVector.at(i).transactionMONTH;
			cout << "/";
			cout << transactionsVector.at(i).transactionYEAR << endl;

			cout << "Items: ";
			cout << transactionsVector.at(i).transactionITEMS << endl << endl;

		}

	}

	if (numberOfTransactionsViewed == 0)
	{
		cout << "No transactions have been found between those dates!" << endl << endl;

		int operation;
		
		cout << "Do you wish to re-search?"<<endl;
		cout << "1. Yes, re-introduce new dates" << endl;
		cout << "2. No, quit to main menu" << endl;
		cout << "Chosen operation: ";
		cin >> operation;

		cout << endl;

		switch (operation)
		{
		case 1:
			searchTransactionPeriod(clientsVector, transactionsVector, productsVector);
		case 2:
			optionsMenu(clientsVector, transactionsVector, productsVector);
		}

	
	}
	optionsMenu(clientsVector, transactionsVector, productsVector);

}
void searchTransactionClient(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector)
{
	unsigned int clientId;

	cout << "Introduce the client ID whose transaction you want to view" << endl << endl;
	cout << "ID: ";
	cin >> clientId;

	cout << endl;

	int numberOfTransactionsViewed=0;

	for (int i = 0; i < transactionsVector.size(); i++)
	{
		if (transactionsVector.at(i).clientID == clientId)
		{
			cout << "Transaction date: ";
			cout << transactionsVector.at(i).transactionDAY;
			cout << "/";
			cout << transactionsVector.at(i).transactionMONTH;
			cout << "/";
			cout << transactionsVector.at(i).transactionYEAR << endl;;

			cout << "Transaction items: ";
			cout << transactionsVector.at(i).transactionITEMS<<endl<<endl;

			numberOfTransactionsViewed++;
		}
	}

	if (numberOfTransactionsViewed == 0)
	{
		unsigned int operation;
		cout << "No transaction was found for that client!" << endl << endl;
		cout << "What do you wish to do?" << endl;
		cout << "1. Search for another id" << endl;
		cout << "2. Quit to main menu" << endl;
		cout << "Chosen option: ";
		cin >> operation;

		cout << endl;

		switch (operation)
		{
		case 1:
			searchTransactionClient(clientsVector, transactionsVector, productsVector);
		case 2:
			optionsMenu(clientsVector, transactionsVector, productsVector);
		}
	}
	else
	{
		cout << "Transactions have been successfuly viewed!" << endl << endl;
		optionsMenu(clientsVector, transactionsVector, productsVector);
	}
}
void searchAllTransactions(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector, vector<string>&productsVector)
{
	cout << "ID   DATE          TRANSACTION ITEMS" << endl<<endl;

	for (int i = 0; i < transactionsVector.size(); i++)
	{
		string date;
		date.append(to_string(transactionsVector.at(i).transactionDAY));
		date.append("/");
		date.append(to_string(transactionsVector.at(i).transactionMONTH));
		date.append("/");
		date.append(to_string(transactionsVector.at(i).transactionYEAR));


		cout << setw(5) << left << transactionsVector.at(i).clientID;

		cout << setw(12) << left << date;

		cout << transactionsVector.at(i).transactionITEMS << endl;
	}
	cout << endl;
	optionsMenu(clientsVector, transactionsVector, productsVector);
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*MENU OPTION THAT CREATES ADVERTISMENT------------------------------------------------------------------------------------------------------------------------*/
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
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*MENU OPTION THAT SAVES INFORMATION ON FILES AND EXITS PROGRAM-----------------------------------------------------------------------------------------------------*/
void exitProgram(vector<client_t>&clientsVector, vector<transaction_t>&transactionsVector)
{//Saves the information on the respective files and ends the proggram
	exitSaveClients(clientsVector);
	exitSaveTransactions(transactionsVector);
	exit(0);
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/

bool confirmChoice()
{//Note: confirm choice only appears on comands that change vectors
	unsigned int operation;

	cout << "Are you sure you want to continue?" << endl;
	cout << "1. Yes" << endl;
	cout << "2. No, return to main menu" << endl;

	cout << "Chosen operation: ";
	cin >> operation;

	cout << endl;

	if (operation == 1)
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
		cout << "Invalid date" << endl << endl;;
		return false;
	}

	int leapMonths[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int notLeapMonths[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (leapYear)
	{
		if (day <= 0 || day > leapMonths[month - 1])
		{
			cout << "Invalid date" << endl<<endl;
			return false;
		}
		else return true;
	}
	else if (day <= 0 || day > notLeapMonths[month - 1])
	{
		cout << "Invalid date" << endl << endl;
		return false;
	}
	else return true;

}
bool verifyDatesOrder(int oldDay, int oldMonth, int oldYear, int recentDay, int recentMonth, int recentYear)
{//Verifies if two given dates are respectively the older and most recent date
	if (!(oldYear <= recentYear))
	{
		cout << "Dates are in incorrect order" << endl << endl;
		return false;
	}
	if (oldYear < recentYear)//if the old year is smaller than the recent one, than it's guaranteed to be a valid date
		return true;

	
	if (!(oldMonth <= recentMonth))
	{
		cout << "Dates are in incorrect order" << endl << endl;
		return false;
	}
	if (oldMonth < recentMonth)  //after comparing the years if the old month is smaller than the recent one, than it's guaranteed to be a valid date
		return true;

	if (!(oldDay <= recentDay))
	{
		cout << "Dates are in incorrect order" << endl << endl;
		return false;
	}
	if (oldDay < recentDay)////after comparing the months if the old day is smaller than the recent one, than it's guaranteed to be a valid date
		return true;
	else
	{
		cout << "Both dates are equal" << endl << endl;
		return false;
	}

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

void exitSaveClients(vector<client_t>&clientsVector)
{//Write client information on client's file
		ofstream clientStream;
		string filename, temporary;
		stringstream stream;
		cout << "Introduce the file where the clients information will be saved: ";
		cin >> filename;
		cin.ignore();
		clientStream.open(filename);
		for (int i = 0; i < clientsVector.size(); i++)
		{
			temporary.append(to_string(clientsVector.at(i).clientID));
			temporary.append(" ; ");
			temporary.append(clientsVector.at(i).clientNAME);
			temporary.append(" ; ");
			stream << fixed << setprecision(2) << clientsVector.at(i).clientSHOP;
			string s = stream.str();
			temporary.append(s);
			stream.clear();
			stream.str(string());
			clientStream << temporary;
			if (!(i == (clientsVector.size() - 1)))
				clientStream << "\n";
			temporary.erase();
		}
	}
void exitSaveTransactions(vector<transaction_t>&transactionsVector)
{//Write transaction information on transaction's file
	ofstream transactionStream;
	string filename, temporary;
	stringstream stream;
	cout << "Introduce the file where the transactions information will be saved: ";
	cin >> filename;
	cin.ignore();
	transactionStream.open(filename);
	for (int i = 0; i < transactionsVector.size(); i++)
	{
	temporary.append(to_string(transactionsVector.at(i).clientID));
	temporary.append(" ; ");
	temporary.append(to_string(transactionsVector.at(i).transactionDAY));
	temporary.append("/");
	temporary.append(to_string(transactionsVector.at(i).transactionMONTH));
	temporary.append("/");
	temporary.append(to_string(transactionsVector.at(i).transactionYEAR));
	temporary.append(" ; ");
	stream << fixed << setprecision(2) << transactionsVector.at(i).transactionITEMS;
	string s = stream.str();
	temporary.append(s);
	stream.clear();
	stream.str(string());
	transactionStream << temporary;
	if (!(i == (transactionsVector.size() - 1)))
		transactionStream << "\n";
	temporary.erase();
	}
}

