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

int getRandomNumber(int min, int max) {
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
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
    cout << "�������� ��������:" << endl;
    cout << "1. �����" << endl;
    cout << "2. ��������" << endl;
    cout << "��� �����: ";
    while ((!(cin >> choice)) || !validation(choice, 1, 2)) {
        cout << "������ �����! ������� (1 ��� 2): ";
        clear();
    }
    return choice;
}

int playBlackjack(const std::array<Card, 52>& deck) {
    int cardIndex = 0; 
    int PlayerTotal = 0;
    int DealerTotal = 0;

    if (cardIndex >= 52) {
        cerr << "������: ������ �����������!" << endl;
        return LOSE;
    }

    cout << "�������� ������� ����� ����� ����� ���:" << endl;
    cout << "1. 11 �����" << endl;
    cout << "2. 1 ����" << endl;
    cout << "��� �����: ";
    int choice(0);
    while ((!(cin >> choice) || !validation(choice, 1, 2))) {
        cout << "������, ������� 1 ��� 2: ";
        clear();
    }
    bool getTuz = (choice == 1);
    cout << endl;


    DealerTotal += getCardValue(deck[cardIndex], getTuz);
    cout << "������ ���� �����, ���������� ����� � ������: " << DealerTotal << " (" << printCard(deck[cardIndex]) << ")" << '\n';
    cardIndex++;

    if (cardIndex >= 52) {
        cerr << "������: ������ �����������!" << endl;
        return LOSE;
    }


    cout << "�� ����� ��� �����.. " << endl;
    PlayerTotal += getCardValue(deck[cardIndex], getTuz);
    cout << "������ ����� - " << "(" << printCard(deck[cardIndex]) << ")" << endl;
    cardIndex++;

    if (cardIndex >= 52) {
        cerr << "������: ������ �����������!" << endl;
        return LOSE;
    }

    PlayerTotal += getCardValue(deck[cardIndex], getTuz);
    cout << "������ ����� - " << "(" << printCard(deck[cardIndex]) << ")" << endl;
    cardIndex++;

    cout << endl;
    cout << "� ���� " << PlayerTotal << " �����" << endl;

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
                    cerr << "������: ������ �����������!" << endl;
                    return LOSE;
                }
                PlayerTotal += getCardValue(deck[cardIndex], getTuz);
                cout << "�� ����� �����.. � ���� " << PlayerTotal << " �����" << " (" << printCard(deck[cardIndex]) << ")" << endl;
                cardIndex++;
            }
            else {
                break;
            }
        }
    }


    while (DealerTotal < 17) {
        if (cardIndex >= 52) {
            cerr << "������: ������ �����������!" << endl;
            return LOSE;
        }
        cout << endl;
        cout << "������ ���� �����.." << " (" << printCard(deck[cardIndex]) << ")" << endl;
        DealerTotal += getCardValue(deck[cardIndex], getTuz);
        cout << "� ������� " << DealerTotal << " �����" << endl;
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