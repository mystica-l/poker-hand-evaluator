#include "HandEvaluator.h"
#include <iostream>
/* HandEvaluator Constructor */
HandEvaluator::HandEvaluator()
{

}

/* evaluateHand */
//Takes in a hand array of varying sizes (5, 6, or 7 cards)
//Calls riverCombinatorics or turnCombinatorics to get all combinations of hands
//Adjusts handStrength to be the highest it can be based on the cards given
void HandEvaluator::evaluateHand(Card handArray[], HandRankings handStrength[], int cardsInHand)
{
  if(cardsInHand == 5)
  {
    evaluateOneHand(handArray, handStrength);
  }
  else if(cardsInHand == 6)
  {
    Card** allHands = turnCombinatorics(handArray);

    for(int i = 0; i < 6; i ++)
    {
      HandRankings temp[6];
      for(int i = 0; i < 6; i ++)
      {
        temp[i] = handStrength[i];
      }
      evaluateOneHand(allHands[i], handStrength);
      if(handToLong(temp) > handToLong(handStrength))
      {
        for(int i = 0; i < 6; i ++)
        {
          handStrength[i] = temp[i];
        }
      }
    }

    for(int i = 0; i < 6; i ++)
    {
      delete [] allHands[i];
    }
    delete [] allHands;
  }
  else
  {
    Card** allHands = riverCombinatorics(handArray);

    for(int i = 0; i < 21; i ++)
    {
      HandRankings temp[6];
      sortHand(allHands[i]);

      for(int i = 0; i < 6; i ++)
      {
        temp[i] = handStrength[i];
      }

      evaluateOneHand(allHands[i], handStrength);
      if(handToLong(temp) > handToLong(handStrength))
      {
        for(int i = 0; i < 6; i ++)
        {
          handStrength[i] = temp[i];
        }
      }
    }

    for(int i = 0; i < 21; i ++)
    {
      delete [] allHands[i];
    }
    delete [] allHands;
  }
}

/* handToLong */
//Turns handStrength into a long integer to easily compare the strength of hands
long long HandEvaluator::handToLong(HandRankings handStrength[])
{
  long long sum = 0;
  for(int i = 0; i < 6; i ++)
  {
    long long addOn = static_cast<int>(handStrength[i]);
    for(int j = 0; j <= 12 - (i * 2); j ++)
    {
      addOn *= 10;
    }
    sum += addOn;
  }
  return sum;
}

/* evaluateOneHand */
//Evaluates a single hand, called by evaluateHands
void HandEvaluator::evaluateOneHand(Card handArray[], HandRankings handStrength[])
{
  sortHand(handArray);
  straightFlush(handArray, handStrength) || quads(handArray, handStrength) || fullHouse(handArray, handStrength) || flush(handArray, handStrength) || straight(handArray, handStrength) || trips(handArray, handStrength) || twoPair(handArray, handStrength) || pair(handArray, handStrength) || highCard(handArray, handStrength);
}

/* riverCombinatorics */
//Takes in an array of 7 cards (2 hole cards, 5 community cards)
//Spits out a pointer to a 2d array of every single combination 5 card hands from 7 cards
Card** HandEvaluator::riverCombinatorics(Card handArray[])
{
  //With the river out, there are 21 different combinations of 5 card hands
  Card** allHands = new Card*[21];
  int handCounter = 0;
  //Loops through each combination once
  for(int i = 0; i < 3; i ++)
  {
    for(int j = i + 1; j < 4; j ++)
    {
      for(int k = j + 1; k < 5; k ++)
      {
        for(int l = k + 1; l < 6; l ++)
        {
          for(int m = l + 1; m < 7; m ++)  
          {
            allHands[handCounter] = new Card[5];
            allHands[handCounter][0] = handArray[i];
            allHands[handCounter][1] = handArray[j];
            allHands[handCounter][2] = handArray[k];
            allHands[handCounter][3] = handArray[l];
            allHands[handCounter][4] = handArray[m];
            handCounter ++;
          }
        }
      }
    }
  }
  return allHands;
}

/* turnCombinatorics */
//Takes in an array of 6 cards (2 hole cards, 4 community cards)
//Spits out a pointer to a 2d array of every single combination 5 card hands from 6 cards
Card** HandEvaluator::turnCombinatorics(Card handArray[])
{
  //With the turn out, there are 6 different combinations of 5 card hands
  Card** allHands = new Card*[6];

  int handCounter = 0;
  for(int i = 0; i < 2; i ++)
  {
    for(int j = i + 1; j < 3; j ++)
    {
      for(int k = j + 1; k < 4; k ++)
      {
        for(int l = k + 1; l < 5; l ++)
        {
          for(int m = l + 1; m < 6; m ++)
          {
            allHands[handCounter] = new Card[5];
            allHands[handCounter][0] = handArray[i];
            allHands[handCounter][1] = handArray[j];
            allHands[handCounter][2] = handArray[k];
            allHands[handCounter][3] = handArray[l];
            allHands[handCounter][4] = handArray[m];
            handCounter ++;
          }
        }
      }
    }
  }
  return allHands; 
}

/* sortHand */
//Sorts hand from least valuable to most valuable card
void HandEvaluator::sortHand(Card handArray[])
{
  //For each card in the array...
  for(int i = 1; i < 5; i ++)
  {
    Card temp = handArray[i];
    int j = i - 1;

    while(j >= 0 && handArray[j].getValue() > temp.getValue())
    {
      handArray[j + 1] = handArray[j];
      j--;
    }
    handArray[j + 1] = temp;
  }
}

/* straightFlush */
bool HandEvaluator::straightFlush(Card handArray[], HandRankings handStrength[])
{
  bool straightFlush = false;
  bool fiveHighStraightFlush = false;
  
  //If the hand is both a straight and a flush...
  if(flush(handArray) && straight(handArray))
  {
    //If the 4th card is a five, it has to be a five high straight flush
    if(handArray[3].getValue() == FIVE)
    {
      fiveHighStraightFlush = true;
    }
    //Set straight flush to true
    else
    {
      straightFlush = true;
    }
  }

  if(straightFlush)
  {
    handStrength[0] = STRAIGHT_FLUSH;
    handStrength[1] = static_cast<HandRankings>(static_cast<int>(handArray[4].getValue()));
    handStrength[2] = NULLRANK;
    handStrength[3] = NULLRANK;
    handStrength[4] = NULLRANK;
    handStrength[5] = NULLRANK;
  }
  else if(fiveHighStraightFlush)
  { 
    handStrength[0] = STRAIGHT_FLUSH;
    handStrength[1] = HAND_FIVE;
    handStrength[2] = NULLRANK;
    handStrength[3] = NULLRANK;
    handStrength[4] = NULLRANK;
    handStrength[5] = NULLRANK;
  }


  return straightFlush;
}

/* quads */
//Returns if there is four of a kind
bool HandEvaluator::quads(Card handArray[], HandRankings handStrength[])
{
  bool quads = false;
  int kickerIndex;

  //If the first 4 cards are the same, quads are true and the kicker index is set to 4
  if(handArray[0].getValue() == handArray[1].getValue() && handArray[1].getValue() == handArray[2].getValue() && handArray[2].getValue() == handArray[3].getValue())
  {
    quads = true;
    kickerIndex = 4;
  }
  //Or if the last 4 cards are the same, quads are true and the kicker index is set to 0
  else if(handArray[1].getValue() == handArray[2].getValue() && handArray[2].getValue() == handArray[3].getValue() && handArray[3].getValue() ==  handArray[4].getValue())
  {
    quads = true;
    kickerIndex = 0;
  }

  if(quads)
  {
    handStrength[0] = QUADS;
    handStrength[1] = static_cast<HandRankings>(static_cast<int>(handArray[2].getValue()));
    handStrength[2] = static_cast<HandRankings>(static_cast<int>(handArray[kickerIndex].getValue()));
    handStrength[3] = NULLRANK;
    handStrength[4] = NULLRANK;
    handStrength[5] = NULLRANK;
  }
  return quads;
}

/* fullHouse */
//Returns if there are 3 of a kind and a pair in the hand and adjusts handStrength
bool HandEvaluator::fullHouse(Card handArray[], HandRankings handStrength[])
{
  bool fullHouse = false;
  int pairIndex;

  //If the first 3 cards are the same
  if(handArray[0].getValue() == handArray[1].getValue() && handArray[1].getValue() == handArray[2].getValue())
  {
    //And the other 2 cards are the same, set fullHouse to true and the pairIndex to 4
    if(handArray[3].getValue() == handArray[4].getValue())
    {
      pairIndex = 4;
      fullHouse = true;
    }
  }
  //Or if the last 3 cards are the same
  else if(handArray[2].getValue() == handArray[3].getValue() && handArray[3].getValue() == handArray[4].getValue())
  {
    //And the first 2 cards are the same, set fullHouse to true and the pairIndex to 4
    if(handArray[0].getValue() == handArray[1].getValue())
    {
      pairIndex = 0;
      fullHouse = true;
    }
  }

  if(fullHouse)
  {
    handStrength[0] = FULL_HOUSE;
    handStrength[1] = static_cast<HandRankings>(static_cast<int>(handArray[2].getValue()));
    handStrength[2] = static_cast<HandRankings>(static_cast<int>(handArray[pairIndex].getValue()));
    handStrength[3] = NULLRANK;
    handStrength[4] = NULLRANK;
    handStrength[5] = NULLRANK;
  }

  return fullHouse;
}

/* flush */
//Returns if all cards are the same suit and adjusts handStrength
bool HandEvaluator::flush(Card handArray[], HandRankings handStrength[])
{
  bool flush = false;

  //Sets to flush to true
  flush = handArray[0].getSuit() == handArray[1].getSuit() && handArray[1].getSuit() == handArray[2].getSuit() && handArray[2].getSuit() == handArray[3].getSuit() && handArray[3].getSuit() == handArray[4].getSuit();

  if(flush)
  {
    handStrength[0] = FLUSH;
    for(int i = 1; i < 6; i ++)
    {
      handStrength[i] = static_cast<HandRankings>(static_cast<int>(handArray[5 - i].getValue()));
    }
  }
  
  return flush;
}

/* flush */
//Returns true if all cards are the same suit
bool HandEvaluator::flush(Card handArray[])
{
  return handArray[0].getSuit() == handArray[1].getSuit() && handArray[1].getSuit() == handArray[2].getSuit() && handArray[2].getSuit() == handArray[3].getSuit() && handArray[3].getSuit() == handArray[4].getSuit();
}

/* straight */
//Returns true if there are 5 cards in sequential order and adjusts handStrength
bool HandEvaluator::straight(Card handArray[], HandRankings handStrength[])
{
  bool fiveHighStraight = false;
  bool straight = false;

  //If the hand is a straight, set straight to true
  if(handArray[0].getValue() == handArray[1].getValue() - 1 && handArray[1].getValue() - 1 == handArray[2].getValue() - 2 && handArray[2].getValue() - 2 == handArray[3].getValue() - 3 && handArray[3].getValue() - 3 == handArray[4].getValue() - 4)
  {
    straight = true;
  }
  //If the hand is a five high straight, set five high straight to true
  else if(handArray[0].getValue() == TWO && handArray[1].getValue() == THREE && handArray[2].getValue() == FOUR && handArray[3].getValue() == FIVE && handArray[4].getValue() == ACE)
  {
    fiveHighStraight = true;
  }
  
  if(straight)
  {
    handStrength[0] = STRAIGHT;
    handStrength[1] = static_cast<HandRankings>(static_cast<int>(handArray[4].getValue()));
    handStrength[2] = NULLRANK;
    handStrength[3] = NULLRANK;
    handStrength[4] = NULLRANK;
    handStrength[5] = NULLRANK;
  }
  else if(fiveHighStraight)
  {
    handStrength[0] = STRAIGHT;
    handStrength[1] = HAND_FIVE;
    handStrength[2] = NULLRANK;
    handStrength[3] = NULLRANK;
    handStrength[4] = NULLRANK;
    handStrength[5] = NULLRANK;
  }
  
  return straight || fiveHighStraight;
}

/* straight */
//Returns true if there are 5 cards in sequential order
bool HandEvaluator::straight(Card handArray[])
{
  if(handArray[0].getValue() == handArray[1].getValue() - 1 && handArray[1].getValue() - 1 == handArray[2].getValue() - 2 && handArray[2].getValue() - 2 == handArray[3].getValue() - 3 && handArray[3].getValue() - 3 == handArray[4].getValue() - 4)
  {
    return true;
  }
  else if(handArray[0].getValue() == TWO && handArray[1].getValue() == THREE && handArray[2].getValue() == FOUR && handArray[3].getValue() == FIVE && handArray[4].getValue() == ACE)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/* trips */
//Returns true if there are 3 of the same cards in the hand and adjusts handStrength
bool HandEvaluator::trips(Card handArray[], HandRankings handStrength[])
{
  bool trips = false;
  int kickerIndex1;
  int kickerIndex2;
  
  //Iterates through the hand to find 3 back to back cards and sets kicker indexes
  for(int i = 0; i < 3; i ++)
  {
    if(handArray[i].getValue() == handArray[i + 1].getValue() && handArray[i + 1].getValue() == handArray[i + 2].getValue())
    {
      trips = true;
      if(i == 0)
      {
        kickerIndex1 = 4;
        kickerIndex2 = 3;
      }
      else if(i == 1)
      {
        kickerIndex1 = 4;
        kickerIndex2 = 0;
      }
      else
      {
        kickerIndex1 = 1;
        kickerIndex2 = 0;
      }
    }
  }

  if(trips)
  {
    handStrength[0] = TRIPS;
    handStrength[1] = static_cast<HandRankings>(static_cast<int>(handArray[2].getValue()));
    handStrength[2] = static_cast<HandRankings>(static_cast<int>(handArray[kickerIndex1].getValue()));
    handStrength[3] = static_cast<HandRankings>(static_cast<int>(handArray[kickerIndex2].getValue()));
    handStrength[4] = NULLRANK;
    handStrength[5] = NULLRANK;
  }

  return trips;
}

/* twoPair */
//Returns true if there are 2 pairs in the hand and adjusts handStrength accordingly
bool HandEvaluator::twoPair(Card handArray[], HandRankings handStrength[])
{
  bool twoPair = false;
  int kickerIndex;
  int higherPairIndex;
  int lowerPairIndex;

  if(handArray[0].getValue() == handArray[1].getValue() && handArray[3].getValue() == handArray[4].getValue())
    {
      twoPair = true;
      higherPairIndex = 4;
      lowerPairIndex = 1;
      kickerIndex = 2;
    }
  else if(handArray[1].getValue() == handArray[2].getValue() && handArray[3].getValue() == handArray[4].getValue())
    {
      twoPair = true;
      higherPairIndex = 4;
      lowerPairIndex = 2;
      kickerIndex = 0;
    }
  else if(handArray[0].getValue() == handArray[1].getValue() && handArray[2].getValue() == handArray[3].getValue())
    {
      twoPair = true;
      higherPairIndex = 3;
      lowerPairIndex = 1;
      kickerIndex = 4;
    }

  if(twoPair)
  {
    handStrength[0] = TWO_PAIR;
    handStrength[1] = static_cast<HandRankings>(static_cast<int>(handArray[higherPairIndex].getValue()));
    handStrength[2] = static_cast<HandRankings>(static_cast<int>(handArray[lowerPairIndex].getValue()));
    handStrength[3] = static_cast<HandRankings>(static_cast<int>(handArray[kickerIndex].getValue()));
    handStrength[4] = NULLRANK;
    handStrength[5] = NULLRANK;
  }

  return twoPair;
}

/* pair */
//Returns true if there are 2 of the same card in the hand and adjusts handStrength
bool HandEvaluator::pair(Card handArray[], HandRankings handStrength[])
{
  bool pair = false;
  int kickerIndex1 = -1;
  int kickerIndex2 = -1;
  int kickerIndex3 = -1;
  int pairIndex1 = 0;
  int pairIndex2 = 0;
  for(int i = 0; i < 4; i ++)
  {
    if(handArray[i].getValue() == handArray[i + 1].getValue())
    {
      pair = true;
      pairIndex1 = i;
      pairIndex2 = i + 1;
    }
  }

  for(int i = 4; i >= 0; i --)
  {
    if(i != pairIndex1 && i != pairIndex2)
    {
      if(kickerIndex1 == -1)
      {
        kickerIndex1 = i;
      }
      else if(kickerIndex2 == -1)
      {
        kickerIndex2 = i;
      }
      else
      {
        kickerIndex3 = i;
      }
    }
  }

  if(pair)
  {
    handStrength[0] = PAIR;
    handStrength[1] = static_cast<HandRankings>(static_cast<int>(handArray[pairIndex1].getValue()));
    handStrength[2] = static_cast<HandRankings>(static_cast<int>(handArray[kickerIndex1].getValue()));
    handStrength[3] = static_cast<HandRankings>(static_cast<int>(handArray[kickerIndex2].getValue()));
    handStrength[4] = static_cast<HandRankings>(static_cast<int>(handArray[kickerIndex3].getValue()));
    handStrength[5] = NULLRANK;
  }

  return pair;
}

/* highCard */
//Adjusts handStrength to the 5 unique cards in the hand
bool HandEvaluator::highCard(Card handArray[], HandRankings handStrength[])
{
    handStrength[0] = HIGH_CARD;
    for(int i = 1; i < 6; i ++)
    {
      handStrength[i] = static_cast<HandRankings>(static_cast<int>(handArray[5 - i].getValue()));
    }

  return true;
}

/* printHand */
//Prints the hand based on the ranking
void HandEvaluator::printHand(HandRankings handStrength[])
{
  switch(handStrength[0])
  {
    case STRAIGHT_FLUSH:
    {
      if(handStrength[1] == HAND_ACE)
      {
        cout << "ROYAL FLUSH!" << endl;
      }
      else
      {
        cout << "Straight Flush, ";
        Card high = Card(SPADES, static_cast<Value>(handStrength[1]));
        cout << high.getValueString() << " high" << endl;
      }
      break;
    }
    case QUADS:
    {
      cout << "Four of a Kind, ";
      Card fourX = Card(SPADES, static_cast<Value>(handStrength[1]));
      cout << fourX.getValueString() << "s" << endl;
      break;
    }
    case FULL_HOUSE:
    {
      cout << "Full House, ";
      Card trips = Card(SPADES, static_cast<Value>(handStrength[1]));
      Card pair = Card(SPADES, static_cast<Value>(handStrength[2]));
      cout << trips.getValueString() << "s " << "full of " << pair.getValueString() << "s" << endl;
      break;
    }
    case FLUSH:
    {
      cout << "Flush, ";
      Card high = Card(SPADES, static_cast<Value>(handStrength[1]));
      cout << high.getValueString() << " high" << endl;
      break;
    }
    case STRAIGHT:
    {
      cout << "Straight, ";
      Card high = Card(SPADES, static_cast<Value>(handStrength[1]));
      cout << high.getValueString() << " high" << endl;
      break;
    }
    case TRIPS:
    {
      cout << "Three of a Kind, ";
      Card trips = Card(SPADES, static_cast<Value>(handStrength[1]));
      cout << trips.getValueString() << "s" << endl;
      break;
    }
    case TWO_PAIR:
    {
      cout << "Two Pairs, ";
      Card pair1 = Card(SPADES, static_cast<Value>(handStrength[1]));
      Card pair2 = Card(SPADES, static_cast<Value>(handStrength[2]));
      cout << pair1.getValueString() << "s and " << pair2.getValueString() << "s" << endl;
      break;
    }
    case PAIR:
    {
      cout << "Pair of ";
      Card pair = Card(SPADES, static_cast<Value>(handStrength[1]));
      cout << pair.getValueString() << "s" << endl;
      break;
    }
    case HIGH_CARD:
    {
      Card high = Card(SPADES, static_cast<Value>(handStrength[1]));
      cout << high.getValueString() << " high" << endl;
      break;
    }
    default:
      cout << "Error!" << endl;
  }
}