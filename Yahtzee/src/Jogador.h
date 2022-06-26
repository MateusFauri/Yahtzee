#pragma once
#include <iostream>
#include <string>
#include <vector>

class Jogador
{
	std::string nome;
	int partidasGanhas{ 0 };
	int chances {3};

	std::vector<int> pontuacoes{};
	std::vector<int> cartela {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	void primeiroRolamento();
	bool repetirJogada();
	void mudarDados(int numerosDados);

public:
	std::vector<int> dados;
	Jogador(std::string nome = " ") : nome(nome) {};

	void setPontuacao(int pont);
	void setChaces(int chances);
	void setCartela(int posicao, int pontuacao);
	void setPartidasGanhas();
	int getPartidasGanhas() const;
	std::string getNome() const;
	int getPontuacao(int posicao) const;
	int getChances() const;
	std::vector<int>& getCartela();

	void mostrarCartela();
	void jogarDados();
	void mostrarDados() const;
	void resetarChances();
	int contarPontos() const;
	void resetarCartela();

	//overloading stream operator
	friend std::ostream& operator<<(std::ostream& os, const Jogador& jogador);
};

