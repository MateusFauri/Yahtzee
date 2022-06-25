#include <iostream>
#include "Jogador.h"
#include "Partida.h"
#include <vector>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Portuguese");
	
	int partidas{};
	int numeroJogadores{};
	std::vector<std::string> jogadores{};

	std::cout << "Quantos partidas serão (1-3): ";
	std::cin >> partidas;

	std::cout << "Quantos jogadores serão (1-3): ";
	std::cin >> numeroJogadores;

	for (int i = 0; i < numeroJogadores; i++)
	{
		std::string buffer;
		std::cout << "Digite o nome do " << i + 1 << " jogador: ";
		std::cin >> buffer;
		jogadores.push_back(buffer);
	}

	Partida partida(jogadores, partidas);

	partida.iniciarPartidas();
	

	return 0;
}