#include "functions.h"
#include <Windows.h>
#include <ctime> 
#include <cstdlib> 
#include <algorithm>

using namespace std;

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    std::array<Card, 52> deck;

    int card = 0;
    for (int suit = 0; suit < MAX_SUITS; ++suit)
        for (int rank = 0; rank < MAX_RANKS; ++rank)
        {
            deck[card].suit = static_cast<CardSuit>(suit);
            deck[card].rank = static_cast<CardRank>(rank);
            ++card;
        }
    while (true) {
        shuffleDeck(deck);

        int result = playBlackjack(deck);

        if (result == WIN) {
            std::cout << "Ты выиграл!\n";
        }
        else if (result == NET) {
            std::cout << "Ничья!\n";
        }
        else {
            std::cout << "Ты проиграл...\n";
        }

        cout << endl;
        cout << "Вы хотите попробовать ещё раз?" << endl;
        cout << "Введите (да/нет): ";

        char choice[10]; 
        cin >> choice;

        if (!Choicing(choice)) 
        {
            cout << endl;
            cout << "Игра окончена. Удачи!";
            cout << endl;
            break;
        }
        cout << endl;
    }
    return 0;
}
