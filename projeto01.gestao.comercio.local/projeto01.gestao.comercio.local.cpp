#include <iostream>
#include<iomanip> 
#include<string>
#include<locale> // ortografia UTF-8
#include<ctime> // data


using namespace std;




void exibirStock(string stock[][5],  int totalProdutos) {

	if (totalProdutos == 0) {
		cout << "Estoque esta vazio!" << endl;
		return;
	}

	cout << endl; 
	cout << ">>> ESTOQUE <<<" << endl; 
	for (int i = 0; i < totalProdutos; i++)
	{
		if (stock[i][0] != "") { 
			cout << "ID: " << stock[i][0] << " | Nome: " << stock[i][1] << " | Valor Compra: " << stock[i][2] << " | Quantidade: " << stock[i][3] << " | Valor Venda: " << stock[i][4] << endl; 
		}
	}
}

void addProduto(string stock[][5], int& totalProdutos, int produtos) {
	
	if (totalProdutos >= produtos) {
		cout << "Estoque cheio!" << endl;
		return;
	}

	cout << endl; 
	cout << "_________________________" << endl;
	cout << ">>> Adicionar Estoque <<<" << endl;
	cout << "-------------------------" << endl;
	cout << endl;

	string dadosProdutos[5];
	string tipos[5] = { "ID", "Nome", "Valor", "Quantidade", "Valor Venda" };

	cin.ignore(); 
	for (int i = 0; i < 5 ; i++)
	{
		cout << "Qual " << tipos[i] << " do produto para registrar ou [0] para sair: ";
		getline(cin, dadosProdutos[i]);
		if (dadosProdutos[0] == "0") {
			return; 
		}
	}    

	for (int i = 0; i < 5; i++)
	{
		stock[totalProdutos][i] = dadosProdutos[i];
	}
	
	totalProdutos++;
	cout << endl;
	cout << "Produto adicionado com sucesso!" << endl;

}	

void excluirProduto(string stock[][5], int& totalProdutos) {

	string idDel;
	int qtdDel;
	cout << endl; 
	cout << "_________________________" << endl;
	cout << ">>> Excluir Estoque <<<" << endl;
	cout << "-------------------------" << endl;
	cout << endl;
	cout << "Qual o ID do produto que deseja excluir: ";
	cin >> idDel;
	bool idEncontrado = false;
	for (int i = 0; i < totalProdutos; i++)
	{
		if (stock[i][0] == idDel) {
			idEncontrado = true;
			cout << "Qual a quantidade que deseja excluir: ";
			cin >> qtdDel; 

			//verifica se a quantidade para excluir é valida
			int quantidadeAtual = stoi(stock[i][3]);
			if (qtdDel > quantidadeAtual) {
				cout << "Quantidade insuficiente no estoque!";
				return;
			}

			//atualiza a quantidade no stock
			quantidadeAtual -= qtdDel;
			stock[i][3] = to_string(quantidadeAtual); 

			//remove o produto da matriz se quantidade chegar a zero
			if (quantidadeAtual == 0) {
				for (int j = i; j < totalProdutos - 1; j++)
				{
					for (int k = 0; k < 5; k++)
					{
						stock[j][k] = stock[j + 1][k];
					}
				}
				totalProdutos--;
				cout << "Produto excluido com sucesso!" << endl;
			}
			else {
				cout << "Quantidade atualizada com sucesso! Quantidade restante: " << stock[i][3] << endl;
			}
			return; //produto encontrado e ajustado
		}  
	}
	if (!idEncontrado) {
		cout << "ID nao encontrado!";
	}
}

void addStockExistente(string stock[][5], int totalProdutos, int produtos) {

	string idAdd;
	int qtdAdd;
	cout << endl;
	cout << "_____________________________" << endl;
	cout << "Atualizar Produto no Estoque " << endl;
	cout << "-----------------------------" << endl;
	cout << "Qual ID do produto que deseja atualizar: ";
	cin >> idAdd;

	bool idEncontrado = false;
	for (int i = 0; i < totalProdutos; i++)
	{
		if (idAdd == stock[i][0]) {
			idEncontrado = true;
			cout << "Qual a quantidade que deseja adicionar: ";
			cin >> qtdAdd;

			int intQtdAtual = stod(stock[i][3]);
			int novaQtd = intQtdAtual + qtdAdd;
			stock[i][3] = to_string(novaQtd);

			cout << "Quantidade atualizada com sucesso! O estoque atual e: " << stock[i][3] << endl;
			break;
		}
	}

	if (!idEncontrado) {
		cout << "ID invalido!" << endl;
	}

}

string obterDataAtual() {
	time_t agora = time(0); //tempo atual em segundos
	tm dataHora;
	localtime_s(&dataHora, &agora); //preenche a estrutura como argumento

	//formata a data dd/mm/aaaa
	char buffer[11]; //buffer para armazenar a data
	strftime(buffer, sizeof(buffer), "%d/%m/%Y", &dataHora);

	return string(buffer); //retorna a data como uma string
} 


void checkout(string stock[][5], int totalProdutos) {

	string idBusca, quantRegistrada;
	string compraAtual[20][3]; //para armazenar os produtos da compra
	int numFatura = 0, numCliente = 0, totalCompras = 0;
	
	cin.ignore();
	do
	{
		cout << endl;
		cout << "____________________" << endl;
		cout << "Registro de vendas " << endl;
		cout << "--------------------" << endl;
		cout << "Digite o ID do produto que deseja registrar ou [0] para finalizar: ";
		getline(cin, idBusca); 

		if (idBusca == "0") {
			return; //encerra e volta para o menu principal
		}  

		bool idEncontrado = false;   
		for (int i = 0; i < totalProdutos; i++)
		{
			if (stock[i][0] == idBusca) {
				idEncontrado = true;   
				cout << "ID registrado...";  

				cout << "Qual a quantidade que deseja registrar: ";
				getline(cin, quantRegistrada); 

				if (stoi(stock[i][3]) >= stoi(quantRegistrada)) {   //verifica se há estoque
					int intQuantidadeStock = stoi(stock[i][3]);
					int intQuantidadeRegistrada = stoi(quantRegistrada);
					int quantFinal = intQuantidadeStock - intQuantidadeRegistrada; 

					stock[i][3] = to_string(quantFinal); //atualiza o estoque

					cout << "Venda registrada com sucesso. Quantidade restante: " << stock[i][3] << endl;

					//adicionar produto a matriz da compra
					compraAtual[totalCompras][0] = stock[i][1];
					compraAtual[totalCompras][1] = stock[i][4];
					compraAtual[totalCompras][2] = quantRegistrada; 
					totalCompras++; 
				}
				else {
					cout << "Quantidade insuficiente no stock."; 
				} 
				break; 
			}
		}
		if (!idEncontrado) {
			cout << "ID incorreto!" << endl; 
		}
		
	} while (true); 

	numFatura++; 
	numCliente++; 
	double troco = 0.0, totalGeral = 0.0, totalIva = 0.0, iva = 0.0; 


	cout << endl;
	cout << "---------------------------------" << endl;
	cout << ">>>>>>>> Talao de Vendas <<<<<<<<" << endl;
	cout << "---------------------------------" << endl;
	cout << "Numero da Fatura: " << numFatura << endl;
	cout << "Numero do Cliente: " << numCliente << endl; 
	cout << "Data: " << obterDataAtual() << endl;

	for (int i = 0; i < totalCompras; i++)
	{
		//valores para o talão
		double intValorUnitario = stod(compraAtual[i][1]); // valor unitario
		iva = intValorUnitario * 0.23; //1,23% iva  
		int intQuantRegistrada = stoi(compraAtual[i][2]); // quantidade comprada
		totalIva = (intValorUnitario + iva) * intQuantRegistrada; //valor total da venda
		totalGeral += totalIva;   

		cout << "_________________________________" << endl;   
		cout << "Nome do Produto: " << compraAtual[i][0] << endl;
		cout << "Quantidade: " << intQuantRegistrada << endl;
		cout << fixed << setprecision(2) << "Valor s/IVA: " << intValorUnitario << endl;
		cout << fixed << setprecision(2) << "IVA: " << iva << endl;
		cout << fixed << setprecision(2) << "Total c/IVA: " << totalIva << endl;
		cout << "---------------------------------" << endl; 
	}

	double valorConsumidor = 0.0;
	do
	{
		cout << "Total Geral da Compra: " << fixed << setprecision(2) << totalGeral << endl;
		cout << "Digite o valor entregue pelo consumidor ou [0] para finalizar a venda: ";
		cin >> valorConsumidor;
		cout << "-------------------------------" << endl; 

		if (valorConsumidor == 0) {
			cout << "Venda cancelada!" << endl; 
			break; 
		}

		bool trocoCerto = false;
		if (valorConsumidor >= totalGeral) {  
			trocoCerto = true; 
			troco = valorConsumidor - totalGeral;
			cout << fixed << setprecision(2) << "Troco: €" << troco; 
			break;
		}
		else {
			cout << "Dinheiro insuficiente! Valor a pagar: €" << fixed << setprecision(2) << totalGeral << endl;
		}
	} while (true);

	cout << endl;
	cout << "------------------------------" << endl;
	cout << "Venda finalizada com sucesso!" << endl;
	cout << "------------------------------" << endl;
	
}

void menu2(string stock[][5], int totalProdutos, int produtos) {
	int selc2;

	do
	{
		cout << endl;
		cout << "1. Adicionar Produto ao Stock" << endl;
		cout << "2. Remover Produto do Stock" << endl;
		cout << "3. Atualizar Stock Existente" << endl;
		cout << "4. Sair" << endl;
		cout << "Escolha uma opcao: ";
		cin >> selc2; 

		switch (selc2) 
		{
		case 1: 
			exibirStock(stock, totalProdutos);
			addProduto(stock, totalProdutos, produtos);
			break;
		case 2:
			exibirStock(stock, totalProdutos);
			excluirProduto(stock, totalProdutos);
			break;
		case 3:
			exibirStock(stock, totalProdutos);
			addStockExistente(stock, totalProdutos, produtos); 
			break;
		case 4:
			cout << "Saindo...";
			break;
		default:
			cout << "Opcao invalida!";
			break;
		}
	} while (selc2 != 4);
}

void menu(string stock[][5], int& totalProdutos, int produtos) { 
	int selc;  
	
	do
	{
		cout << endl;
		cout << "____________________________________" << endl;
		cout << "Selecione uma opcao para continuar: " << endl;
		cout << "------------------------------------" << endl;
		cout << "1. Efetuar venda" << endl;
		cout << "2. Gestao do Stock" << endl;
		cout << "3. Sair" << endl;
		cout << "Escolha uma opcao: ";
		cin >> selc;

		switch (selc)
		{
		case 1:
			checkout(stock, totalProdutos); 
			break;
		case 2:
			menu2(stock, totalProdutos, produtos);
			break;
		case 3:
			cout << "Saindo...";
			break;
		default:
			cout << "Opcao invalida!";
			break;
		}

	} while (selc != 3);
}

int main() {

	setlocale(LC_ALL, "");

	//stock
	const int produtos = 20, colunas = 5; 
	string stock[produtos][colunas]; 
	int totalProdutos = 2; 

	stock[0][0] = "101";
	stock[0][1] = "T-Shirt";
	stock[0][2] = "17.0";
	stock[0][3] = "30";
	stock[0][4] = "22.1"; 

	stock[1][0] = "102";
	stock[1][1] = "Bermuda";
	stock[1][2] = "24.0";
	stock[1][3] = "35";
	stock[1][4] = "31.2"; 


	menu(stock, totalProdutos, produtos);    
	return 0;   

}



/*
//funcao para verificar se uma string contem apenas letras e espacos
bool validarString(const string& str) {
	for (char ch : str) {
		// verifica se o caractere nao e uma letra nem um espaco
		if (!isalpha(ch) && !isspace(ch) && isdigit(ch)) {
			return false; //se encontrar um caractere invalido, retorna falso
		}
	}
	return true; //se todos os caracteres forem verdadeiro, retorna verdadeiro
}

//funcao para solicitar uma string valida ao usuario
string solicitarString(const string& mensagem) {
	string entrada;
	while (true)
	{
		cout << mensagem;
		getline(cin, entrada);

		if (validarString(entrada)) {
			return entrada; //retorna string se for valida
		}
		else {
			cout << "Entrada invalida! Use apenas letras e espacos." << endl;
		}
	}
} 
*/