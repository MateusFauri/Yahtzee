#include <iostream>
#include "Jogador.h"
#include "Partida.h"
#include <vector>

int main()
{
	int partidas{};
	int numeroJogadores{};
	std::vector<std::string> jogadores{};
	
	std::cout << "Quantos jogadores serão: ";
	std::cin >> numeroJogadores;

	for (int i = 0; i < numeroJogadores; i++)
	{
		std::string buffer;
		std::cout << "Digite o nome do " << i + 1 << " jogador: ";
		std::cin >> buffer;
		jogadores.push_back(buffer);
	}

	std::cout << "Quantos partiads serão: ";
	std::cin >> partidas;

	Partida partida(jogadores, partidas);

	partida.mostrarJogadores();
	partida.iniciarPartidas();


	return 0;
}