#include "Jogador.h"
#include <stdlib.h>
#include <iomanip> 
#include <cctype>

const int totalTabela = 40;
const int numeracao = 3;
const int legendasTabela = 20;
const int pontuacaoTabela = 4;

void tabelaPontos();
void linhaTabela(std::string linha, int numero);
void lines(char a);

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


void Jogador::jogarDados()
{
	//por enquanto ele renova todo os dados, sem chance de escolher qual quer rolar novamente.
	for (int i = 0; i < dados.size(); i++)  
	{
		dados[i] = rand() % 6 + 1;
		std::cout << "Dado["<< i + 1 << "]: " << dados[i] << std::endl;
	}

	char resp{ ' ' };
	do
	{
		std::cout << "Voce gostaria de rolar algum dos dados novamente? [S/N] " << std::endl;
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


	//marcarPonto();
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
	for (int i = 0; i < dados.size(); i++)
	{
		std::cout << "Dado[" << i + 1 << "]: " << dados[i] << std::endl;
	}
}

bool Jogador::marcarPonto()
{
	tabelaPontos();
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




