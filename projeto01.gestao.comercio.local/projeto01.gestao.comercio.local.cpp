#include <iostream>
#include<iomanip> 
#include<string>
#include<locale>

using namespace std;


void exibirStock(string stock[][20],  int totalProdutos) {

	if (totalProdutos == 0) {
		cout << "Estoque está vazio!" << endl;
		return;
	}

	cout << endl; 
	cout << ">>> ESTOQUE <<<" << endl; 
	for (int i = 0; i < totalProdutos; i++)
	{
		if (stock[i][0] != "") { 
			cout << "ID: " << stock[i][0] << " | Nome: " << stock[i][1] << " | Valor: " << stock[i][2] << " | Quantidade: " << stock[i][3] << endl;
		}
	}

}

void addProduto(string stock[][20], int& totalProdutos, int produtos) {
	
	if (totalProdutos >= produtos) {
		cout << "Estoque cheio!" << endl;
		return;
	}

	cout << endl; 
	cout << "_________________________" << endl;
	cout << ">>> Adicionar Estoque <<<" << endl;
	cout << "-------------------------" << endl;
	exibirStock(stock, totalProdutos);
	cout << endl;

	string dadosProdutos[4];
	string tipos[4] = { "ID", "Nome", "Valor", "Quantidade" };

	cin.ignore(); 
	for (int i = 0; i < 4 ; i++)
	{
		cout << "Qual " << tipos[i] << " do produto: ";
		getline(cin, dadosProdutos[i]);
	}
	

	for (int i = 0; i < 4; i++)
	{
		stock[totalProdutos][i] = dadosProdutos[i];
	}
	
	totalProdutos++;
	cout << endl;
	cout << "Produto adicionado com sucesso!" << endl;

}	

void excluirProduto(string stock[][20], int& totalProdutos) {

	string idDel;
	cout << endl; 
	cout << "_________________________" << endl;
	cout << ">>> Excluir Estoque <<<" << endl;
	cout << "-------------------------" << endl;
	exibirStock(stock, totalProdutos);
	cout << endl;
	cout << "Qual o ID do produto que deseja excluir: ";
	cin >> idDel;
	for (int i = 0; i < totalProdutos; i++)
	{
		if (stock[i][0] == idDel) {
			for (int j = i; j < totalProdutos; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					stock[j][k] = stock[j + 1][k];
				}
			}
		}
		totalProdutos--;
		cout << "Produto excluído com sucesso!" << endl;
		break; 
	}
	

}

void checkout(string stock[][20], int totalProdutos) {

	string idBusca, quantVenda;
	do
	{
		cout << endl;
		cout << "____________________" << endl;
		cout << "Registro de vendas " << endl;
		cout << "--------------------" << endl;
		cout << "Digite o ID do produto que deseja registrar ou [sair] para finalizar: ";
		getline(cin, idBusca); 
		bool idEncontrado = false;  
		for (int i = 0; i < totalProdutos; i++)
		{
			if (stock[i][0] == idBusca) {
				idEncontrado = true;  
				cout << "ID registrado..."; 
				cout << "Qual a quantidade que deseja registrar: ";
				getline(cin, quantVenda); 
				if (stoi(stock[i][3]) >= stoi(quantVenda)) { 
					int quantidadeStock = stoi(stock[i][3]);
					int quantidadeVenda = stoi(quantVenda);
					int quantFinal = quantidadeStock - quantidadeVenda;
					stock[i][3] = to_string(quantFinal);
					cout << "Venda registrada com sucesso. Quantidade restante: " << stock[i][3] << endl;
				}
				else {
					cout << "Quantidade insuficiente no stock.";
				}
			}
			break;
		}
		if (!idEncontrado) {
			cout << "ID incorreto!" << endl; 
		}
		cout << endl;
	} while (idBusca != "sair"); 
	

	
}

void menu(string stock[][20], int& totalProdutos, int produtos) { 
	int selc;
	
	do
	{
		cout << endl;
		cout << "____________________________________" << endl;
		cout << "Selecione uma opção para continuar: " << endl;
		cout << "------------------------------------" << endl;
		cout << "1. Efetuar venda" << endl;
		cout << "2. Adicionar Produto ao Stock" << endl;
		cout << "3. Remover Produto do Stock" << endl;
		cout << "4. Exibir Stock Atual" << endl;
		cout << "5. Sair" << endl;
		cout << "Escolha uma opcao: ";
		cin >> selc;

		switch (selc)
		{
		case 1:
			checkout(stock, totalProdutos); 
			break;
		case 2:
			addProduto(stock, totalProdutos, produtos);  
			break;
		case 3:
			excluirProduto(stock, totalProdutos); 
			break;
		case 4:
			exibirStock(stock, totalProdutos);  
			break;
		case 5:
			cout << "Saindo...";
		default:
			break;
		}

	} while (selc != 5);
}


int main() {

	setlocale(LC_ALL, "");

	//stock
	const int produtos = 20, colunas = 20; 
	string stock[produtos][colunas]; 
	int totalProdutos = 2; 

	stock[0][0] = "101";
	stock[0][1] = "T-Shirt";
	stock[0][2] = "17.0";
	stock[0][3] = "30";

	stock[1][0] = "102";
	stock[1][1] = "Bermuda";
	stock[1][2] = "24.0";
	stock[1][3] = "35";


	//menu
	menu(stock, totalProdutos, produtos);   
	return 0;
}





