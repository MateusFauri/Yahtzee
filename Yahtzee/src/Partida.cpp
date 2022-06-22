#include "Partida.h"
#include <cstdlib>
#include <iomanip> 
#include <cctype>
#include <iterator>
#include <set>


const int totalTabela = 40;
const int numeracao = 3;
const int legendasTabela = 20;
const int pontuacaoTabela = 4;
const int numeroDados = 5;

void tabelaPontos();
void linhaTabela(std::string linha, int numero);
void lines(char a);
bool yatzy(std::set<int>::iterator iterador, std::vector<int>& cartela);


void Partida::iniciarPartidas()
{
	for (int i = 0; i < partidas; ++i)
	{
		for (auto& jogador : jogadores)
		{
			jogador.rolarDados();
		}
		//vencedor = compararPontos(std::vector<Jogadores>& jogadores);
	}
	//mostrarVencedor();
	//acabarJogo();
}

bool Partida::marcarPonto(Jogador &jogador, int tipoPonto)
{
	tabelaPontos();
	do
	{
		std::cout << "Qual ponto voce quer marcar? (Use a numeraçao ao lado dela) ";
		std::cin >> tipoPonto;
	} while (!(tipoPonto > 0 && tipoPonto < 16));

	if (tipoPonto < 7) //mudar o sete para constante
	{
		//Colocar logica de soma de numeros aqui
	}
	else
	{
		std::set<int> numerosContidos{};
		for (int i = 0; i < numeroDados; i++)
		{
			numerosContidos.insert(jogador.dados[i]);
		}
		std::set<int>::iterator iterador = numerosContidos.begin();

		std::vector<int>& cartela = jogador.getCartela();

		switch (numerosContidos.size())
		{
		case 1:
			yatzy(iterador, cartela);
			break;
		case 2:
			//contendoDois();
			break;
		case 3:
			//contendoTres();
			break;
		case 4:
			//contendoQuatro();
			break;
		case 5:
			//contendoCinco();
			break;
		default:
			//Lançar um erro aqui!
			break;
		}
	}
	return true;
}


bool yatzy(std::set<int>::iterator iterador, std::vector<int>& cartela)
{
	if (cartela[14] != 0)
		return false; //ja marcou fullhouse
	cartela[14] = *iterador * 5;
	std::cout << cartela[14] << std::endl;
	return true;
}

//Funções para mostrar melhor no prompt

void lines(char a)
{
	std::cout << std::setw(totalTabela)
		<< std::setfill(a)
		<< ""
		<< std::endl;

	std::cout << std::setfill(' ');
}

void linhaTabela(std::string linha, int numero)
{
	lines('-');
	std::cout << std::setw(numeracao) << std::left << numero
		<< std::setw(legendasTabela) << std::left << linha
		<< std::setw(pontuacaoTabela) << std::left << "| "
		<< std::setw(pontuacaoTabela) << std::left << "| "
		<< std::setw(pontuacaoTabela) << std::left << "| "
		<< std::setw(pontuacaoTabela) << std::left << "| "
		<< std::endl;
}

void tabelaPontos()
{
	lines('*');
	std::cout << std::setw((totalTabela - 14) / 2) << "" << "Tabela Yahtzee" << std::endl;
	lines('*');
	std::cout << std::setw(numeracao) << std::left << "#"
		<< std::setw(legendasTabela) << std::left << "Descricao"
		<< std::setw(pontuacaoTabela) << std::left << "|1P |"
		<< std::setw(pontuacaoTabela) << std::left << "2P |"
		<< std::setw(pontuacaoTabela) << std::left << "3P |"
		<< std::setw(pontuacaoTabela) << std::left << " F "
		<< std::endl;
	linhaTabela("Uns ", 1);
	linhaTabela("Dois ", 2);
	linhaTabela("Tres ", 3);
	linhaTabela("Quatro ", 4);
	linhaTabela("Cinco ", 5);
	linhaTabela("Seis ", 6);
	linhaTabela("Par ", 7);
	linhaTabela("Dois Pares ", 8);
	linhaTabela("Trinca ", 9);
	linhaTabela("Quadrupla ", 10);
	linhaTabela("Full House ", 11);
	linhaTabela("Sequencia baixa ", 12);
	linhaTabela("Sequencia alta ", 13);
	linhaTabela("Chance ", 14);
	linhaTabela("Yatzy ", 15);
	lines('*');
}

