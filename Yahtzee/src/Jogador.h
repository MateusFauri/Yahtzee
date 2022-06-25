#pragma once
#include <iostream>
#include <string>
#include <vector>

class Jogador
{
	std::string nome;
	int pontuacao {0};
	int partidasGanhas{ 0 };
	int chances {3};
	
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
	int getPontuacao() const;
	int getChances() const;
	std::vector<int>& getCartela();

	void mostrarCartela();
	void jogarDados();
	void mostrarDados() const;
	void resetarChances();

	//overloading operator
	bool operator==(const Jogador& rhs) const; 
	bool operator<(const Jogador& rhs) const;

	//overloading stream operator
	friend std::ostream& operator<<(std::ostream& os, const Jogador& jogador);
};

