#pragma once
#include <iostream>
#include <string>
#include <vector>

class Jogador
{
	std::string nome;
	int pontuacao {0};
	int chances {3};
	std::vector<int> dados;
	std::vector<int> cartela {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

public:
	Jogador(std::string nome = " ") : nome(nome) {};

	void setPontuacao(int pont);
	void setChaces(int chances);
	void setDados(int posicao, int valor);
	std::string getNome() const;
	int getPontuacao() const;
	int getChances() const;
	std::vector<int> getCartela();

	void primeiroRolamento();
	void jogarDados();
	bool repetirJogada();
	bool marcarPonto(int tipoPonto);
	void mudarDados(int numerosDados);
	void mostrarDados() const;
};

