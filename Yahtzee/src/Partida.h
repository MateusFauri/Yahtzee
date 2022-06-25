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

	Partida(std::vector<std::string>& nomeJogadores, int partidas)
	{
		this->partidas = partidas;

		for (auto& nomeJogador : nomeJogadores)
		{
			Jogador jogador(nomeJogador);
			jogadores.push_back(jogador);
		}
	};
	~Partida() = default;

	int getPartidas() const { return partidas; }
	auto getJogadores() const { return jogadores; }

	void iniciarPartidas();
	void marcarPonto(Jogador& jogador);
	void mostrarJogadores() const;
	std::string compararJogadores(std::vector<Jogador>& jogadores);
	void resetarCartelasJogadores(std::vector<Jogador>& jogadores);
	void contarPartidasGanhas(std::vector<Jogador> jogadores, std::vector<std::string> ganhadores);
	void mostrarVencedores() const;
	void mostrarVencedor(std::vector<Jogador> jogadores) const;
	void fimDeJogo();
};


