#include "Partida.h"
#include <cstdlib>
#include <iomanip> 
#include <sstream>
#include <cctype>

//transformar tudo em enums depois
const int totalTabela = 40;
const int numeracao = 3;
const int legendasTabela = 20;
const int pontuacaoTabela = 4;
const int numeroDados = 5;
const int rangeDado = 6;
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
int quantosTemNoVetor(const std::vector<int>& dados, const int numero);
bool validate(std::string buffer, int& partidas, int range);

void Partida::iniciarPartidas()
{
	for (int i = 0; i < partidas; ++i)
	{
		std::cout << "Começa a partida " << i + 1 << ":" << std::endl;
		for (auto& jogador : jogadores)
		{
			std::cout << "Bem-vindo " << jogador.getNome() << "! Seus dados são: " << std::endl;
			//fazer a validação da resposta de outros rolamentos melhor 
			//ver como posso fazer com stringstream
			jogador.jogarDados();
			escolhaPonto(jogador);
			jogador.setPontuacao(jogador.contarPontos());
			jogador.resetarChances();
		}
		if (jogadores.size() > 1)
		{
			ganhadores.push_back(compararJogadores(jogadores,i));
			std::cout << "O Ganhador da rodada " << i + 1 << " foi " << ganhadores[i] << "!" << std::endl;
		}
		else
		{
			std::cout << "Você fez " << jogadores[0].getPontuacao(i) << " pontos nessa partida!" << std::endl;
		}
		resetarCartelasJogadores(jogadores);
	}
	if (jogadores.size() > 1)
	{
		std::cout << "Lista de vencedores das partidas: " << std::endl;
		mostrarVencedores();
		contarPartidasGanhas(jogadores, ganhadores);
		mostrarVencedor(jogadores);
	}
	fimDeJogo();
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

void Partida::escolhaPonto(Jogador &jogador)
{
	tabelaPontos();
	int tipoPonto{ 0 };
	std::string buffer{};
	//doing validation for the inputs 
	do
	{
		std::cout << "Qual ponto voce quer marcar? (Use a numeraçao ao lado dela) ";
		std::cin >> buffer;
	} while (!validate(buffer, tipoPonto, yatzy));
	
	std::set<int> numerosContidos{};
	for (int i = 0; i < numeroDados; i++)
	{
		numerosContidos.insert(jogador.dados[i]);
	}
	std::set<int>::iterator iterador = numerosContidos.begin();

	while(!marcarPonto(tipoPonto, numerosContidos, jogador))
		std::cout << "Você não pode marcar esse ponto. Tente novamente!" << std::endl;

	jogador.mostrarCartela();
}

std::string Partida::compararJogadores(std::vector<Jogador>& jogadores, int partida)
{
	std::vector<std::string> ganhadores;
	int maiorPontuacao = jogadores.at(0).getPontuacao(partida);
	ganhadores.push_back(jogadores.at(0).getNome());
	for (const auto& jogador : jogadores)
	{
		if (jogador.getPontuacao(partida) > maiorPontuacao)
		{
			ganhadores.pop_back();
			ganhadores.push_back(jogador.getNome());
			maiorPontuacao = jogador.getPontuacao(partida);
		}
		else if (jogador.getPontuacao(partida) == maiorPontuacao)
		{
			ganhadores.push_back(jogador.getNome());
		}
	}
	if (ganhadores.size() == 1)
		return ganhadores[0];
	else
		return "Empate!";
}

void Partida::resetarCartelasJogadores(std::vector<Jogador>& jogadores)
{
	for(auto& jogador:jogadores)
		jogador.resetarCartela();
}

void Partida::contarPartidasGanhas(std::vector<Jogador> jogadores, std::vector<std::string> ganhadores)
{
	for (auto& jogador : jogadores)
	{
		for (const auto& ganhador : ganhadores)
		{
			if (ganhador.compare(jogador.getNome()) == 0)
				jogador.setPartidasGanhas();
		}
	}
}

void Partida::mostrarVencedores() const
{
	int i{ 0 };
	for(const auto& ganhador:ganhadores)
	{
		std::cout << "Ganhador da " << i + 1 << " partida foi: " << ganhador << std::endl;
		i++;
	}
}

void Partida::mostrarVencedor(std::vector<Jogador> jogadores)  const
{
	std::vector<Jogador> buffer;
	buffer.push_back(jogadores.at(0));
	for (const auto& jogador : jogadores)
	{
		if (jogador.getPartidasGanhas() > buffer.at(0).getPartidasGanhas())
		{
			buffer.pop_back();
			buffer.push_back(jogador);
		}
		else if (jogador.getPartidasGanhas() == buffer.at(0).getPartidasGanhas())
		{
			buffer.push_back(jogador);
		}
	}
	if (buffer.size() == 1)
		std::cout << "O ganhor do jogo foi " << buffer.at(0).getNome() << " com " << buffer.at(0).getPartidasGanhas() << " partidas ganhas!" << std::endl;
	else
		std::cout << "Não Houve ganhador no final das contas.... Por que não jogam de novo?" << std::endl;
}

void Partida::fimDeJogo()
{
	std::cout << "Fim de Jogo!" << std::endl;
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

	//sum of players points 

int somaSimples(int tipoPonto, Jogador& jogador)
{
	int soma{ 0 };
	for (const auto& dado : jogador.dados)
	{
		if (dado == tipoPonto)
			soma += dado;
	}
	return soma;
}

int somaPar(Jogador& jogador, int numero)
{
	int count {0};
	for (const auto& dado : jogador.dados)
	{
		if (dado == numero)
			count += 1;
	}
	return (count > 1) ? (count * 2) : 0;
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


	//data validation
bool validate(std::string buffer, int& partidas, int range)
{
	std::istringstream validator{ buffer };
	if (validator >> partidas)
		if (partidas > 0 && partidas <= range)
			return true;
		else
		{
			std::cout << "Sorry, it's only in the range of 1 to " << range <<"! try again." << std::endl;
			return false;
		}
	else
	{
		std::cout << "Sorry, that's not a integer! try again." << std::endl;
		return false;
	}
}

bool Partida::marcarPonto(int tipoPonto, std::set<int> numerosContidos, Jogador& jogador)
{
	if ((tipoPonto > 0 && tipoPonto <= pontosSoma) || (tipoPonto == chance))
	{
		if (jogador.getCartela()[tipoPonto - 1] == 0)
		{
			int ponto = somaSimples(tipoPonto, jogador);
			if (ponto > 0)
			{
				jogador.setCartela(tipoPonto - 1, ponto);
				return true;
			}
		}
		else if (jogador.getCartela()[tipoPonto - 1] == 0 && tipoPonto == chance)
		{
			int soma{ 0 };
			auto it = numerosContidos.begin();
			for (it; it != numerosContidos.end(); it++)
			{
				soma += *it;
			}
			jogador.setCartela(tipoPonto - 1, soma);
			return true;
		}
	}
	else if ((tipoPonto == sequenciaBaixa || tipoPonto == sequenciaAlta) && numerosContidos.size() == 5)
	{
		if (jogador.getCartela()[tipoPonto - 1] == 0 && tipoPonto == sequenciaBaixa)
		{
			if ((numerosContidos.count(1) != 0) && (numerosContidos.count(2) != 0) && (numerosContidos.count(3) != 0) && (numerosContidos.count(4) != 0) && (numerosContidos.count(5) != 0))
			{
				// 15 é os pontos da sequencia baixa
				jogador.setCartela(tipoPonto - 1, 15);
				return true;
			}
		}
		else if (jogador.getCartela()[tipoPonto - 1] == 0 && tipoPonto == sequenciaAlta)
		{
			if ((numerosContidos.count(2) != 0) && (numerosContidos.count(3) != 0) && (numerosContidos.count(4) != 0) && (numerosContidos.count(5) != 0) && (numerosContidos.count(6) != 0))
			{
				// 20 é os pontos da sequencia alta
				jogador.setCartela(tipoPonto - 1, 20);
				return true;
			}
		}
	}
	else if ((tipoPonto == par) && (numerosContidos.size() <= 4))
	{
		if (jogador.getCartela()[tipoPonto - 1] == 0)
		{
			int numero{};
			std::string buffer{  };
			do {
				std::cout << "Qual numero você quer escolher: ";
				std::cin >> buffer;
			} while (!validate(buffer, numero, rangeDado));
			
			if (somaPar(jogador, numero) != 0)
			{
				jogador.setCartela(tipoPonto - 1, somaPar(jogador, numero));
				return true;
			}
			else {
				std::cout << "Não da para fazer par com este numero" << std::endl;
			}
		}
	}
	else if ((tipoPonto == doisPares || tipoPonto == trinca) && (numerosContidos.size() <= 3))
	{
		if ((tipoPonto == doisPares) && (jogador.getCartela()[tipoPonto - 1] == 0))
		{
			int numero1, numero2;
			std::string buffer{  };
			do {
				std::cout << "Qual o primeiro numero: ";
				std::cin >> buffer;
			} while (!validate(buffer, numero1, rangeDado));
			do {
				std::cout << "Qual o segundo numero numero: ";
				std::cin >> buffer;
			} while (!validate(buffer, numero2, rangeDado));
			numero1 = somaPar(jogador, numero1);
			numero2 = somaPar(jogador, numero2);
			if (numero1 != 0 && numero2 != 0)
			{
				jogador.setCartela(tipoPonto - 1, numero1 + numero2);
				return true;
			}
			else {
				std::cout << "Não da para fazer par com este numero" << std::endl;
			}
		}
		else if ((tipoPonto == trinca) && (jogador.getCartela()[tipoPonto - 1] == 0))
		{
			int numero;
			std::string buffer{  };
			do {
				std::cout << "Qual numero você quer escolher: ";
				std::cin >> buffer;
			} while (!validate(buffer, numero, rangeDado));
			numero = somaTrinca(jogador, numero);
			if (numero != 0)
			{
				jogador.setCartela(tipoPonto - 1, numero);
				return true;
			}
			else {
				std::cout << "Não da para fazer trinca com este numero" << std::endl;
			}
		}
	}
	else if ((tipoPonto == fullHouse || tipoPonto == quadrupla) && (numerosContidos.size() <= 2))
	{
		if (jogador.getCartela()[tipoPonto - 1] == 0 && tipoPonto == fullHouse)
		{
			auto itBegin = numerosContidos.begin();
			auto itLast = itBegin++;

			int maisNumeros{ *itBegin };
			int menosNumeros{ *itLast };
			if (numerosContidos.count(*itBegin) < numerosContidos.count(*itLast))
			{
				maisNumeros = *itLast;
				menosNumeros = *itBegin;
			}
			jogador.setCartela(tipoPonto - 1, somafullHouse(menosNumeros, maisNumeros));
			return true;
		}
		else if (jogador.getCartela()[tipoPonto - 1] == 0 && tipoPonto == quadrupla)
		{
			auto it = numerosContidos.begin();
			for (it; it != numerosContidos.end(); it++)
			{
				if (quantosTemNoVetor(jogador.dados, *it) > 3)
				{
					jogador.setCartela(tipoPonto - 1, somaQuadrupla(*it));
					return true;
				}
			}
		}
	}
	else if ((tipoPonto == yatzy) && (numerosContidos.size() == 1))
	{
		if (jogador.getCartela()[tipoPonto - 1] == 0)
		{
			std::set<int>::iterator it = numerosContidos.begin();
			jogador.setCartela(tipoPonto - 1, yatzyPonto(*it));
			return true;
		}
	}

	return false;
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
