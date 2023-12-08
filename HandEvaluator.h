#ifndef HANDEVALUATOR_H
#define HANDEVALUATOR_H

#include "Card.h"
#include <vector>
class HandEvaluator
{
public:
  HandEvaluator();
  void evaluateHand(Card[], HandRankings[], int);
  long long handToLong(HandRankings[]);
  void printHand(HandRankings[]);

private:
  Card** riverCombinatorics(Card[]);
  Card** turnCombinatorics(Card[]);
  void sortHand(Card[]);
  void evaluateOneHand(Card[], HandRankings[]);
  bool straightFlush(Card[], HandRankings[]);
  bool quads(Card[], HandRankings[]);
  bool fullHouse(Card[], HandRankings[]);
  bool flush(Card[], HandRankings[]);
  bool flush(Card[]);
  bool straight(Card[], HandRankings[]);
  bool straight(Card[]);
  bool trips(Card[], HandRankings[]);
  bool twoPair(Card[], HandRankings[]);
  bool pair(Card[], HandRankings[]);
  bool highCard(Card[], HandRankings[]);
};

#endif