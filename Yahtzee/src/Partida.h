#pragma once
#include "Jogador.h"
#include <string>
#include <set>
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
	void mostrarJogadores() const;
	void mostrarVencedores() const;
	void mostrarVencedor(std::vector<Jogador> jogadores) const;

	bool marcarPonto(int tipoPonto, std::set<int> numerosContidos, Jogador& jogador);
	void iniciarPartidas();
	void escolhaPonto(Jogador& jogador);
	std::string compararJogadores(std::vector<Jogador>& jogadores, int partida);
	void resetarCartelasJogadores(std::vector<Jogador>& jogadores);
	void contarPartidasGanhas(std::vector<Jogador> jogadores, std::vector<std::string> ganhadores);
	void fimDeJogo();
};


