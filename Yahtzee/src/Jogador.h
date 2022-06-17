#pragma once
#include <iostream>
#include <string>
#include <array>

class Jogador
{
	std::string nome;
	int pontuacao {0};
	int chances {3};
	std::array<int, 5> dados {0,0,0,0,0};
	std::array<bool, 15> cartela;

public:
	Jogador(std::string nome = " ") : nome(nome) { cartela.fill(false); };

	void setPontuacao(int pont);
	void setChaces(int chances);
	void setDados(int posicao, int valor);
	std::string getNome() const;
	int getPontuacao() const;
	int getChances() const;


	void jogarDados();
	bool repetirJogada();
	bool marcarPonto();
	void mudarDados(int numerosDados);
	void mostrarDados() const;
};

