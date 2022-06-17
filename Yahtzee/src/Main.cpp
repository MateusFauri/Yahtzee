#include <iostream>
#include "Jogador.h"

int main()
{
	Jogador j1("Mateus");
	std::cout << "Nome do jogador 1: " << j1.getNome() << std::endl;
	j1.jogarDados();
	



	return 0;
}