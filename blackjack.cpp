#include "functions.h"
#include <Windows.h>
#include <ctime> 
#include <cstdlib> 

using namespace std;


int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(static_cast<unsigned int>(time(0)));
	std::array<Card, 52> deck;

	int card = 0;
	for (int suit = 0; suit < MAX_SUITS; ++suit)
		for (int rank = 0; rank < MAX_RANKS; ++rank)
		{
			deck[card].suit = static_cast<CardSuit>(suit);
			deck[card].rank = static_cast<CardRank>(rank);
			++card;
		}
	shuffleDeck(deck);

	int result = playBlackjack(deck);

	if (result == WIN)
	{
		std::cout << "Ты выиграл!\n";
	}
	else if (result == NET)
	{
		std::cout << "Ничья!\n";
	}
	else
	{
		std::cout << "Ты проиграл...\n";
	}

	return 0;
}