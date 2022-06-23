#include "Jogador.h"
#include <cstdlib>
#include <cctype>
#include <iterator>
#include <ctime>


const int numeroDados = 5;

void Jogador::setPontuacao(int pont)
{
	this->pontuacao = pont;
}

void Jogador::setChaces(int chances)
{
	this->chances = chances;
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
	std::cout << "Quantos dados você quer mudar? ";
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
		std::cout << "Posicao do " << i + 1 << "° dado para mudança: ";
		//fazer uma verificação melhor dos dados inseridos aqui
		std::cin >> posicaoDado;
		//verificar se o numero temporario esta certo
		tempDado = rand() % 6 + 1;
		dados[--posicaoDado] = tempDado;

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

bool Jogador::operator==(const Jogador& rhs) const
{
	if (pontuacao == rhs.pontuacao)
		return true;
	else
		return false;
}

bool Jogador::operator<(const Jogador& rhs) const
{
	if (pontuacao < rhs.pontuacao)
		return true;
	else
		return false;
}

std::ostream& operator<<(std::ostream& os, const Jogador& jogador)
{
	os << "O jogador " << jogador.nome << " tem " << jogador.pontuacao << " pontos";
	return os;
}
