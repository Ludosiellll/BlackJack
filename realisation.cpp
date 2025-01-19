#include "functions.h"

using namespace std;

void clear(char delimiter) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), delimiter);
}

string printCard(const Card& card) {
    string result;

    switch (card.rank) {
    case RANK_2:     result += "2"; break;
    case RANK_3:     result += "3"; break;
    case RANK_4:     result += "4"; break;
    case RANK_5:     result += "5"; break;
    case RANK_6:     result += "6"; break;
    case RANK_7:     result += "7"; break;
    case RANK_8:     result += "8"; break;
    case RANK_9:     result += "9"; break;
    case RANK_10:    result += "T"; break;
    case RANK_VALET: result += "V"; break;
    case RANK_DAMA:  result += "D"; break;
    case RANK_KOROL: result += "K"; break;
    case RANK_TYZ:   result += "T"; break;
    }

    switch (card.suit) {
    case SUIT_TREFU: result += "TR"; break;
    case SUIT_BYBNU: result += "B"; break;
    case SUIT_CHERVU: result += "CH"; break;
    case SUIT_PIKI:   result += "P"; break;
    }

    return result;
}

void printDeck(const std::array<Card, 52>& deck) {
    for (const auto& card : deck) {
        cout << printCard(card) << ' ';
    }
    cout << '\n';
}

void swapCard(Card& a, Card& b) {
    Card temp = a;
    a = b;
    b = temp;
}

mt19937 gen(std::random_device{}());

int getRandomNumber(int min, int max) {
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

void shuffleDeck(std::array<Card, 52>& deck) {
    for (int i = 0; i < deck.size(); i++) {
        int swapIndex = getRandomNumber(0, 51);
        swapCard(deck[i], deck[swapIndex]);
    }
}

int getCardValue(const Card& card, bool getTuz) {
    switch (card.rank) {
    case RANK_2:     return 2;
    case RANK_3:     return 3;
    case RANK_4:     return 4;
    case RANK_5:     return 5;
    case RANK_6:     return 6;
    case RANK_7:     return 7;
    case RANK_8:     return 8;
    case RANK_9:     return 9;
    case RANK_10:    return 10;
    case RANK_VALET: return 10;
    case RANK_DAMA:  return 10;
    case RANK_KOROL: return 10;
    case RANK_TYZ:   return getTuz ? 11 : 1;
    }
    return 0;
}

bool validation(int number, int min, int max) {
    return (number >= min && number <= max);
}

int getPlayerChoice() {
    int choice(0);
    cout << "Выберите действие:" << endl;
    cout << "1. Взять" << endl;
    cout << "2. Оставить" << endl;
    cout << "Ваш выбор: ";
    while ((!(cin >> choice)) || !validation(choice, 1, 2)) {
        cout << "Ошибка ввода! Введите (1 или 2): ";
        clear();
    }
    return choice;
}



int playBlackjack(const std::array<Card, 52>& deck) {
    int cardIndex = 0; 
    int PlayerTotal = 0;
    int DealerTotal = 0;

    if (cardIndex >= 52) {
        cerr << "Ошибка: колода закончилась!" << endl;
        return LOSE;
    }

    cout << "Выберите сколько очков будет иметь туз:" << endl;
    cout << "1. 11 очков" << endl;
    cout << "2. 1 очко" << endl;
    cout << "Ваш выбор: ";
    int choice(0);
    while ((!(cin >> choice) || !validation(choice, 1, 2))) {
        cout << "Ошибка, введите 1 или 2: ";
        clear();
    }
    bool getTuz = (choice == 1);
    cout << endl;


    DealerTotal += getCardValue(deck[cardIndex], getTuz);
    cout << "Диллер берёт карту, количество очков у Дилера: " << DealerTotal << " (" << printCard(deck[cardIndex]) << ")" << '\n';
    cardIndex++;
    cout << endl;

    if (cardIndex >= 52) {
        cerr << "Ошибка: колода закончилась!" << endl;
        return LOSE;
    }


    cout << "Ты берёшь две карты.. " << endl;
    PlayerTotal += getCardValue(deck[cardIndex], getTuz);
    cout << "Первая карта - " << "(" << printCard(deck[cardIndex]) << ")" << endl;
    cardIndex++;

    if (cardIndex >= 52) {
        cerr << "Ошибка: колода закончилась!" << endl;
        return LOSE;
    }

    PlayerTotal += getCardValue(deck[cardIndex], getTuz);
    cout << "Вторая карта - " << "(" << printCard(deck[cardIndex]) << ")" << endl;
    cardIndex++;

    cout << endl;
    cout << "У тебя " << PlayerTotal << " очков" << endl;

    while (true) {
        if (PlayerTotal > 21) {
            return LOSE;
        }
        else {
            cout << endl;
            int choice = getPlayerChoice();
            cout << endl;
            if (choice == 1) {
                if (cardIndex >= 52) {
                    cerr << "Ошибка: колода закончилась!" << endl;
                    return LOSE;
                }
                PlayerTotal += getCardValue(deck[cardIndex], getTuz);
                cout << "Ты берёшь карту.. У тебя " << PlayerTotal << " очков" << " (" << printCard(deck[cardIndex]) << ")" << endl;
                cardIndex++;
            }
            else {
                break;
            }
        }
    }


    while (DealerTotal < 17) {
        if (cardIndex >= 52) {
            cerr << "Ошибка: колода закончилась!" << endl;
            return LOSE;
        }
        cout << endl;
        cout << "Диллер берёт карту.." << " (" << printCard(deck[cardIndex]) << ")" << endl;
        DealerTotal += getCardValue(deck[cardIndex], getTuz);
        cout << "У Диллера " << DealerTotal << " очков" << endl;
        cardIndex++;
    }


    if (DealerTotal > 21) {
        return WIN;
    }
    else if (PlayerTotal == DealerTotal) {
        return NET;
    }
    else {
        return (PlayerTotal > DealerTotal) ? WIN : LOSE;
    }
}

char toLowerCyrillic(char c) {
    // Преобразуем символы кириллицы в нижний регистр
    if (c >= 'А' && c <= 'Я') {
        return c + 32; // Сдвигаем код символа на 32 (разница между 'А' и 'а' в Windows-1251)
    }
    return tolower(c); // Для остальных символов используем стандартный tolower
}

bool Choicing(const char choice[]) {

    char firstChar = toLowerCyrillic(choice[0]);

    while (firstChar != 'д' && firstChar != 'н') {
        cout << "Ошибка ввода! Введите 'Да' или 'Нет': ";
        clear();

        char newChoice[10];
        cin >> newChoice;

        firstChar = toLowerCyrillic(newChoice[0]);
    }

    return firstChar == 'д';
}
