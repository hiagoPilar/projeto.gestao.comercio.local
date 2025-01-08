#include <iostream>
#include<string>

using namespace std;

void menu() {
	int opcao;
	do
	{
		cout << "1. Efetuar venda" << endl;
		cout << "2. Criar artigo novo" << endl;
		cout << "3. Adicionar stock a artigo existente" << endl;
		cout << "4. Eliminar produto" << endl;
		cout << "5. Sair" << endl;
		cout << "Escolha uma opcao: ";
		cin >> opcao;

		switch (opcao)
		{
		case 1:
			//funcao para efetuar venda
			funcEfetuarVenda();
			break;
		case 2:
			//funcao criar artigo novo
			break;
		case 3:
			//adicionar stock a artigo existente
			adicionarStock();
			break;
		case 4:
			//funcao eliminar produto
			break;
		case 5:
			cout << "Saindo..." << endl;
			break;
		default:
			cout << "Opcao invalida!";
		}
	} while (opcao != 5);
}

void funcEfetuarVenda() {

}

void adicionarStock(int id, int quantidade) { 
		
}

int main() {

	menu();
	return 0;

	//stock
	int id[3] = { 101, 102, 103 };
	string nome[3] = { "T-Shirt", "Bermuda", "Tenis" };
	float preco[3] = { 15.0, 25.0, 70.0 };
	int quantidade[3] = {}


}
