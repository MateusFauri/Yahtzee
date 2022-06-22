#include <iostream>
#include "Jogador.h"
#include "Partida.h"
#include <vector>

int main()
{
	int partidas = 1;
	Jogador j1("Mateus");
	std::cout << "Nome do jogador 1: " << j1.getNome() << std::endl;
	std::vector<Jogador> jogadores{};
	jogadores.push_back(j1);

	Partida partida(jogadores,partidas);


	//partida.marcarPonto(j1, 11);
	


	return 0;
}