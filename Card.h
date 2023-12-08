#ifndef CARD_H
#define CARD_H

#include "Constants.h"
#include <string>

class Card
{
public:
  Card();
  Card(Suit, Value);
  Suit getSuit();
  Value getValue();
  string toString();
  string getValueString();
protected:
  Suit suit;
  Value value;
};
#endif
