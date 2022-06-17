#include "Jogador.h"
#include <cstdlib>
#include <iomanip> 
#include <cctype>
#include <set>
#include <vector>
#include <ctime>

const int totalTabela = 40;
const int numeracao = 3;
const int legendasTabela = 20;
const int pontuacaoTabela = 4;
const int numeroDados = 5;

void tabelaPontos();
void linhaTabela(std::string linha, int numero);
void lines(char a);
bool yatzy(std::set<int>::iterator iterador, std::vector<int>& cartela );

void Jogador::setPontuacao(int pont)
{
	this->pontuacao = pont;
}

void Jogador::setChaces(int chances)
{
	this->chances = chances;
}

void Jogador::setDados(int posicao, int valor)
{
	dados.at(posicao) = valor;
}

std::string Jogador::getNome() const
{
	return nome;
}

int Jogador::getPontuacao() const
{
	return pontuacao;
}

int Jogador::getChances() const
{
	return chances;
}

std::vector<int> Jogador::getCartela()
{
	return cartela;
}

void Jogador::primeiroRolamento()
{
	srand((unsigned)time(0));
	dados.clear();
	for (int i = 0; i < numeroDados; i++)
	{
		dados.push_back(rand()%(6) + 1);
		//dados.push_back(4);
		std::cout << "Dado[" << i + 1 << "]: " << dados[i] << std::endl;
	}
}

void Jogador::jogarDados()
{
	primeiroRolamento();

	char resp{ ' ' };
	do
	{
		std::cout << "Voce gostaria de rolar algum dos dados novamente? [S/N] ";
		std::cin >> resp;
		if (toupper(resp) == 'S')
		{
			if (!repetirJogada())
				break;
		}
		else if (toupper(resp) == 'N')
			break;
		else
			std::cout << "Não entendi sua resposta. Tente novamente..." << std::endl;
	} while (true);

	tabelaPontos();
	int tipoPonto{ 0 };
	do
	{
		std::cout << "Qual ponto voce quer marcar? (Use a numeraçao ao lado dela) ";
		std::cin >> tipoPonto;
	} while (!(tipoPonto > 0 && tipoPonto < 16));

	marcarPonto(tipoPonto);
}

bool Jogador::repetirJogada()
{
	if (chances == 0)
	{
		std::cout << "Você não tem mais chances para jogar." << std::endl;
		return false;
	}
	chances--;
	int numeroDados{ 0 };
	std::cout << "Quantos dados você quer mudar? " << std::endl;
	//arrumar erro de dados invalidos
	std::cin >> numeroDados;
	mudarDados(numeroDados);

	std::cout << "Agora você tem " << chances << " chances restantes" << std::endl;
	mostrarDados();
	return true;
}

//posso mudar para bool depois, assim retornar false quando tratar os erros das leituras dos dados.
void Jogador::mudarDados(int numerosDados)
{
	for (int i = 0; i < numerosDados; i++)
	{
		int posicaoDado{ 0 };
		int tempDado{ 0 };
		std::cout << "Posicao do " << i + 1 << "° dado para mudança: " << std::endl;
		//fazer uma verificação melhor dos dados inseridos aqui
		std::cin >> posicaoDado;
		//verificar se o numero temporario esta certo
		tempDado = rand() % 6 + 1;
		setDados(--posicaoDado, tempDado);
	}
}

void Jogador::mostrarDados() const
{
	if (dados.empty())
	{
		std::cout << "Não há dados para mostrar!" << std::endl;
	}
	else
	{
		for (int i = 0; i < numeroDados; i++)
		{
			std::cout << "Dado[" << i + 1 << "]: " << dados[i] << std::endl;
		}
	}
}

bool Jogador::marcarPonto(int tipoPonto)
{
	if (tipoPonto < 7) //mudar o sete para constante
	{
		//Colocar logica de soma de numeros aqui
	}
	else
	{
		std::set<int> numerosContidos {};
		for (int i=0; i < numeroDados; i++)
		{
			numerosContidos.insert(dados[i]);
		}
		std::set<int>::iterator iterador = numerosContidos.begin();

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
	std::cout << std::setw((totalTabela - 14)/2) <<"" << "Tabela Yahtzee" << std::endl;
	lines('*');
	std::cout << std::setw(numeracao) << std::left << "#"
		<< std::setw(legendasTabela) << std::left << "Descricao"
		<< std::setw(pontuacaoTabela) << std::left << "|1P |"
		<< std::setw(pontuacaoTabela) << std::left << "2P |"
		<< std::setw(pontuacaoTabela) << std::left << "3P |"
		<< std::setw(pontuacaoTabela) << std::left << " F "
		<< std::endl;
	linhaTabela("Uns ",1);
	linhaTabela("Dois ",2);
	linhaTabela("Tres ",3);
	linhaTabela("Quatro ",4);
	linhaTabela("Cinco ",5);
	linhaTabela("Seis ",6);
	linhaTabela("Par ",7);
	linhaTabela("Dois Pares ",8);
	linhaTabela("Trinca ",9);
	linhaTabela("Quadrupla ",10);
	linhaTabela("Full House ",11);
	linhaTabela("Sequencia baixa ",12);
	linhaTabela("Sequencia alta ",13);
	linhaTabela("Chance ",14);
	linhaTabela("Yatzy ",15);
	lines('*');
}




