#include <iostream>
#include<iomanip> 
#include<string>
#include<locale>


using namespace std;


void exibirStock(string stock[][4],  int totalProdutos) {

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

void addProduto(string stock[][4], int& totalProdutos, int produtos) {
	
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

void excluirProduto(string stock[][4], int& totalProdutos) {

	string idDel;
	cout << endl; 
	cout << "_________________________" << endl;
	cout << ">>> Excluir Estoque <<<" << endl;
	cout << "-------------------------" << endl;
	exibirStock(stock, totalProdutos);
	cout << endl;
	cout << "Qual o ID do produto que deseja excluir: ";
	cin >> idDel;
	bool idEncontrado = false;
	for (int i = 0; i < totalProdutos; i++)
	{
		if (stock[i][0] == idDel) {
			idEncontrado = true;
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
	if (!idEncontrado) {
		cout << "ID não encontrado!";
	}
}

void checkout(string stock[][4], int totalProdutos) {

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
		cout << "Digite o ID do produto que deseja registrar ou [sair] para finalizar: ";
		getline(cin, idBusca); 

		if (idBusca == "sair") {
			break; //encerra e volta para o menu principal
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
					compraAtual[totalCompras][1] = stock[i][2];
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
	cout << ">>>>>>>> Talão de Vendas <<<<<<<<" << endl;
	cout << "---------------------------------" << endl;
	cout << "Número da Fatura: " << numFatura << endl;
	cout << "Número do Cliente: " << numCliente << endl; 
	cout << "Data: " << endl;  

	for (int i = 0; i < totalCompras; i++)
	{
		//valores para o talão
		double intValorUnitario = stod(compraAtual[i][1]); // valor unitario
		iva = intValorUnitario * 0.3; //30% iva  
		int intQuantRegistrada = stoi(compraAtual[i][2]); // quantidade comprada
		totalIva = (intValorUnitario + iva) * intQuantRegistrada; //valor total da venda
		totalGeral += totalIva;   

		cout << "_________________________________" << endl;   
		cout << "Nome do Produto: " << compraAtual[i][0] << endl;
		cout << "Quantidade: " << intQuantRegistrada << endl;
		cout << fixed << setprecision(2) << "Valor s/IVA: €" << intValorUnitario << endl;
		cout << fixed << setprecision(2) << "IVA: €" << iva << endl;
		cout << fixed << setprecision(2) << "Total c/IVA: €" << totalIva << endl;
		cout << "---------------------------------" << endl; 
	}

	double valorConsumidor = 0.0;
	do
	{
		cout << endl;
		cout << "Total Geral da Compra: €" << fixed << setprecision(2) << totalGeral << endl;
		cout << "Digite o valor entregue pelo consumidor ou [0] para finalizar a venda: ";
		cin >> valorConsumidor;

		if (valorConsumidor == 0) {
			cout << "Venda cancelada!" << endl; 
			break;
		}

		bool trocoCerto = false;
		if (valorConsumidor >= totalGeral) {  
			trocoCerto = true; 
			troco = valorConsumidor - totalGeral;
			cout << fixed << setprecision(2) << "Troco: €" << troco << endl; 
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

void menu(string stock[][4], int& totalProdutos, int produtos) { 
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
			cout << "Opção inválida!";
			break;
		}

	} while (selc != 5);
}

int main() {

	setlocale(LC_ALL, "");

	//stock
	const int produtos = 20, colunas = 4; 
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





