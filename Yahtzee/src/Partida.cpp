#include "Partida.h"
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
const int pontosSoma = 6;
const int par = 7;
const int doisPares = 8;
const int trinca = 9;
const int quadrupla = 10;
const int fullHouse = 11;
const int sequenciaBaixa = 12;
const int sequenciaAlta = 13;
const int chance = 14;
const int yatzy = 15;

void tabelaPontos();
void linhaTabela(std::string linha, int numero);
void lines(char a);
int yatzyPonto(int numero);
int somaSimples(int tipoPonto, Jogador& jogador);
int somaPar(Jogador& jogador, int numero);
int somaTrinca(Jogador& jogador, int numero);
int somafullHouse(int menosNumeros, int maisNumeros);
int somaQuadrupla(int numero);
bool validacaoPontos(int tipoPonto, std::set<int> numerosContidos, Jogador& jogador);
int quantosTemNoVetor(const std::vector<int>& dados, const int numero);


void Partida::iniciarPartidas()
{
	for (int i = 0; i < partidas; ++i)
	{
		for (auto& jogador : jogadores)
		{
			jogador.jogarDados();
			marcarPonto(jogador);
		}
		//vencedor = compararPontos(std::vector<Jogadores>& jogadores);
	}
	//mostrarVencedor();
	//acabarJogo();
}

bool Partida::marcarPonto(Jogador &jogador)
{
	tabelaPontos();
	int tipoPonto{ 0 };

	std::set<int> numerosContidos{};
	for (int i = 0; i < numeroDados; i++)
	{
		numerosContidos.insert(jogador.dados[i]);
	}
	std::set<int>::iterator iterador = numerosContidos.begin();

	do
	{
		std::cout << "Qual ponto voce quer marcar? (Use a numeraçao ao lado dela) ";
		std::cin >> tipoPonto;
	} while (!validacaoPontos(tipoPonto, numerosContidos,jogador));


	return true;
}

void Partida::mostrarJogadores() const
{
	if (jogadores.empty())
		std::cout << "Não há jogadores" << std::endl;
	else {
		for (int i = 0; i < jogadores.size(); i++)
		{
			std::cout << jogadores[i] << std::endl;
		}
	}
}



bool validacaoPontos(int tipoPonto, std::set<int> numerosContidos, Jogador& jogador)
{
	std::vector<int> cartela = jogador.getCartela();

	if ((tipoPonto > 0) && (tipoPonto <= pontosSoma) && (numerosContidos.count(tipoPonto) > 0))
	{
		if (cartela[--tipoPonto] == 0)
		{
			cartela[--tipoPonto] = somaSimples(tipoPonto, jogador);
			return true;
		}
	}
	else if ((tipoPonto == sequenciaBaixa || tipoPonto == sequenciaAlta || tipoPonto == chance) && numerosContidos.size() == 5)
	{
		if (cartela[--tipoPonto] == 0 && tipoPonto == sequenciaBaixa)
		{
			if ((numerosContidos.count(1) != 0) && (numerosContidos.count(2) != 0) && (numerosContidos.count(3) != 0) && (numerosContidos.count(4) != 0) && (numerosContidos.count(5) != 0))
			{
				// 15 é os pontos da sequencia baixa
				cartela[--tipoPonto] = 15;
				return true;
			}
		}
		else if (cartela[--tipoPonto] == 0 && tipoPonto == sequenciaAlta)
		{
			if ((numerosContidos.count(2) != 0) && (numerosContidos.count(3) != 0) && (numerosContidos.count(4) != 0) && (numerosContidos.count(5) != 0) && (numerosContidos.count(6) != 0))
			{
				// 20 é os pontos da sequencia alta
				cartela[--tipoPonto] = 20;
				return true;
			}
		}
		else if (cartela[--tipoPonto] == 0 && tipoPonto == chance)
		{
			int soma{ 0 };
			auto it = numerosContidos.begin();
			for (it; it != numerosContidos.end(); it++)
			{
				soma += *it;
			}
			cartela[--tipoPonto] = soma;
			return true;
		}
	}
	else if ((tipoPonto == par) && (numerosContidos.size() <= 4))
	{

		if (cartela[--tipoPonto] == 0)
		{
			int numero;
			std::cout << "Qual numero você quer escolher: ";
			std::cin >> numero;
			if (somaPar(jogador, numero) != 0)
			{
				cartela[--tipoPonto] = somaPar(jogador, numero);
				return true;
			}
			else {
				std::cout << "Não da para fazer par com este numero" << std::endl;
			}
		}
	}
	else if ((tipoPonto == doisPares || tipoPonto == trinca) && (numerosContidos.size() <= 3))
	{

		if (cartela[--tipoPonto] == 0 && tipoPonto == doisPares)
		{
			int numero1,numero2;
			std::cout << "Quais numeros você quer escolher: ";
			std::cin >> numero1 >> numero2;
			numero1 = somaPar(jogador, numero1);
			numero2 = somaPar(jogador, numero2);
			if ( numero1 != 0 &&  numero2 != 0)
			{
				cartela[--tipoPonto] =  numero1 + numero2;
				return true;
			}
			else {
				std::cout << "Não da para fazer par com este numero" << std::endl;
			}
		}
		else if (cartela[--tipoPonto] == 0 && tipoPonto == trinca)
		{
			int numero;
			std::cout << "Qual numero você quer escolher: ";
			std::cin >> numero;
			numero = somaTrinca(jogador, numero);
			if (numero != 0)
			{
				cartela[--tipoPonto] = numero;
				return true;
			}
			else {
				std::cout << "Não da para fazer par com este numero" << std::endl;
			}
		}
	}
	else if ((tipoPonto == fullHouse || tipoPonto == quadrupla) && (numerosContidos.size() <= 2))
	{
		if (cartela[--tipoPonto] == 0 && tipoPonto == fullHouse)
		{
			auto it = numerosContidos.begin();
			int maisNumeros{ *it };
			int menosNumeros{ *(++it) };
			if (numerosContidos.count(*it) < numerosContidos.count(*(++it)))
			{
				maisNumeros = *(++it);
				menosNumeros = *it;
			}
			cartela[--tipoPonto] = somafullHouse(menosNumeros, maisNumeros);
			return true;
		}
		else if (cartela[--tipoPonto] == 0 && tipoPonto == quadrupla)
		{
			auto it = numerosContidos.begin();
			for (it; it != numerosContidos.end(); it++)
			{
				if (quantosTemNoVetor(jogador.dados, *it) > 3)
				{
					cartela[--tipoPonto] = somaQuadrupla(*it);
					return true;
				}
			}
		}
	}
	else if ((tipoPonto == yatzy) && (numerosContidos.size() == 1))
	{
		if (cartela[--tipoPonto] == 0)
		{
			std::set<int>::iterator it = numerosContidos.begin();
			cartela[--tipoPonto] = yatzyPonto(*it);
			return true;
		}
	}
	std::cout << "Você não pode marcar esse ponto. Tente novamente!" << std::endl;
	return false;
}

int somaSimples(int tipoPonto, Jogador& jogador)
{
	int soma{ 0 };
	for (int i = 0; i < jogador.dados.size(); i++)
	{
		if (jogador.dados[i] == tipoPonto)
			soma += jogador.dados[i];
	}
	return soma;
}

int somaPar(Jogador& jogador, int numero)
{
	int count {0};
	for(int i=0; i < jogador.dados.size(); i++)
	{
		if (jogador.dados[i] == numero)	
			count++;
	}
	return count > 1 ? (count * 2): 0;
}

int somaTrinca(Jogador& jogador, int numero)
{
	int count{ 0 };
	for (int i = 0; i < jogador.dados.size(); i++)
	{
		if (jogador.dados[i] == numero)
			count++;
	}
	return count > 2 ? (count * 3) : 0;
}

int somaQuadrupla(int numero)
{
	return numero * 4;
}

int somafullHouse(int menosNumeros, int maisNumeros)
{
	return (menosNumeros * 2) + (maisNumeros * 3);
}


int yatzyPonto(int numero)
{
	return numero * 5;
}


int quantosTemNoVetor(const std::vector<int>& dados, const int numero)
{
	int soma{ 0 };
	for (auto& dado : dados)
	{
		if (dado == numero) soma++;
	}

	return soma;
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
	linhaTabela("Par ", par);
	linhaTabela("Dois Pares ", doisPares);
	linhaTabela("Trinca ", trinca);
	linhaTabela("Quadrupla ", quadrupla);
	linhaTabela("Full House ", fullHouse);
	linhaTabela("Sequencia baixa ", sequenciaBaixa);
	linhaTabela("Sequencia alta ", sequenciaAlta);
	linhaTabela("Chance ", chance);
	linhaTabela("Yatzy ", yatzy);
	lines('*');
}
