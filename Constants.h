#ifndef CONSTANT_H
#define CONSTANT_H

using namespace std;

//Enumerated types for the cards
enum Suit {SPADES = 1, HEARTS, DIAMONDS, CLUBS};

enum Value {TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};

//Enumerated types for ranking hands
enum HandRankings {STRAIGHT_FLUSH = 9, QUADS = 8, FULL_HOUSE = 7, FLUSH = 6, STRAIGHT = 5, TRIPS = 4, TWO_PAIR = 3, PAIR = 2, HIGH_CARD = 1,
                   HAND_TWO = 2, HAND_THREE, HAND_FOUR, HAND_FIVE, HAND_SIX, HAND_SEVEN, HAND_EIGHT, HAND_NINE, HAND_TEN, HAND_JACK, HAND_QUEEN, HAND_KING, HAND_ACE, NULLRANK = 0};

#endif
