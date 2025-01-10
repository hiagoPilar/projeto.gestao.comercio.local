#include <iostream>
#include<iomanip> 
#include<string>
#include<locale>

using namespace std;

void exibirStock(string stock[][20], int totalProdutos) { 
	
	if (totalProdutos == 0) {
		cout << "O estoque está vazio!" << endl;
		return;
	}

	//stock existente
	stock[0][0] = "101";
	stock[0][1] = "T-Shirt";
	stock[0][2] = "15.0";
	stock[0][3] = "20";

	stock[1][0] = "102";
	stock[1][1] = "Bermuda";
	stock[1][2] = "45.0";
	stock[1][3] = "35";
	
	cout << endl; 
	cout << ">>> Produtos no Estoque <<< "<< endl;
	for (int i = 0; i < totalProdutos; i++) 
	{
		if (stock[i][0] != "") {
			cout << "ID: " << stock[i][0] << " | Nome: " << stock[i][1] << " | Preço: " << stock[i][2] << " | Quantidade: " << stock[i][3] << endl;
		}
	}
}

void adicionarStock(string stock[][20], int& totalProdutos, int linhas) {

	if (totalProdutos >= linhas) {
		cout << "Estoque cheio! Não é possível adicionar mais produtos." << endl;
		return;
	}

	//vetor para armazenar os dados do produto
	string dadosProduto[4];
	string tipos[4] = { "ID", "Nome", "Preco", "Quantidade" };
	
	//adicionar os dados do novo produto
	for (int i = 0; i < 4; i++)
	{
		cout << "Digite o " << tipos[i] << " do produto: ";
		getline(cin, dadosProduto[i]); //le os dados do produto  
		cin.ignore(); 
	}

	//adiciona os dados ao stock
	for (int i = 0; i < 4; i++)
	{
		stock[totalProdutos][i] = dadosProduto[i]; //preenche as colunas do produto
	}

	totalProdutos++; 
	cout << "Produto adicionado com sucesso!" << endl;

} 

void menu(string stock[][20], int& totalProdutos, int linhas) {   
	int opcao; 
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
		cin >> opcao;

		switch (opcao)
		{
		case 1:
			//funcEfetuarVenda(); 
			break;
		case 2:
			adicionarStock(stock, totalProdutos, linhas);
			break;
		case 3:
			//removerProduto();
			break;
		case 4:
			exibirStock(stock, totalProdutos);  
			break;
		case 5:
			cout << "Saindo..." << endl;
			break;
		default:
			cout << "Opcao invalida!";
		}
	} while (opcao != 5);
}

int main() {

	setlocale(LC_ALL, "");

	//gestão de stock
	const int linhas = 20, colunas = 20;
	string stock[linhas][colunas];
	int totalProdutos = 2; 

	//menu principal
	menu(stock, totalProdutos, linhas);  
	return 0; 
}
