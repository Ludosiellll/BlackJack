#pragma once

#include <array>
#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>

enum CardRank {
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_9,
    RANK_10,
    RANK_VALET,
    RANK_DAMA,
    RANK_KOROL,
    RANK_TYZ,
    MAX_RANKS
};

enum CardSuit {
    SUIT_TREFU,
    SUIT_BYBNU,
    SUIT_CHERVU,
    SUIT_PIKI,
    MAX_SUITS
};

struct Card {
    CardRank rank;
    CardSuit suit;
};

enum GameResult {
    LOSE,
    WIN,
    NET
};

void clear(char delimiter = '\n');
std::string printCard(const Card& card);
void printDeck(const std::array<Card, 52>& deck);
void swapCard(Card& a, Card& b);
int getRandomNumber(int min, int max);
void shuffleDeck(std::array<Card, 52>& deck);
int getCardValue(const Card& card, bool getTuz);
bool validation(int number, int min, int max);
int getPlayerChoice();
int playBlackjack(const std::array<Card, 52>& deck);