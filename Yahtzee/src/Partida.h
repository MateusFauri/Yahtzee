#pragma once
#include "Jogador.h"
#include <string>
#include <vector>

class Partida
{
	int partidas;
	std::vector<Jogador> jogadores;
	std::vector<std::string> ganhadores;

public:

	Partida(std::vector<Jogador>& jogadores, int partidas)
	{
		this->partidas = partidas;

		for (auto& jogador : jogadores)
		{
			this->jogadores.push_back(jogador);
		}
	};
	~Partida() = default;

	int getPartidas() const { return partidas; }
	auto getJogadores() const { return jogadores; }

	void iniciarPartidas();
	bool marcarPonto(Jogador& jogador, int tipoPonto);
	/*
	void mostrarVencedores();
	void ganhar();
	bool acabarPartida();
	*/
};


