#include <iostream>
#include "Jogador.h"
#include "Partida.h"
#include <vector>
#include <locale.h>
#include <iomanip>
#include <sstream>

bool validate(std::string buffer, int& partidas);

int main()
{
	setlocale(LC_ALL, "Portuguese");

	std::string buffer{};
	int partidas{};
	int numeroJogadores{};
	std::vector<std::string> jogadores{};

	//doing validation for the inputs 
	do {
		std::cout << "Quantos partidas serão (1-3): ";
		std::cin >> buffer;
	} while (!validate(buffer, partidas));

	do {
		std::cout << "Quantos jogadores serão (1-3): ";
		std::cin >> buffer;
	} while (!validate(buffer, numeroJogadores));

	//catching the name of players
	for (int i = 0; i < numeroJogadores; i++)
	{
		std::string buffer;
		std::cout << "Digite o nome do " << i + 1 << " jogador: ";
		std::cin >> buffer;
		jogadores.push_back(buffer);
	}

	Partida partida(jogadores, partidas);
	//starting the game
	partida.iniciarPartidas();
	

	return 0;
}


bool validate(std::string buffer, int& partidas)
{
	std::istringstream validator{ buffer };
	if (validator >> partidas)
		if (partidas > 0 && partidas < 4)
			return true;
		else
		{
			std::cout << "Sorry, it's only in the range of 1 to 3! try again." << std::endl;
			return false;
		}
	else
	{
		std::cout << "Sorry, that's not a integer! try again." << std::endl;
		return false;
	}
}