#include "Card.h"
#include <iostream>
using namespace std;
/* Default Constructor */
Card::Card()
{
  suit = SPADES;
  value = ACE;
}

/* Overloaded Constructor */
Card::Card(Suit suit, Value value)
{
  this->suit = suit;
  this->value = value;
}

/* getSuit */
//Returns suit enumerated type
Suit Card::getSuit()
{
  return suit;
}

/* getValue */
//Returns value enumerated type
Value Card::getValue()
{
  return value;
}

/* toString */
//Returns the card in string form
string Card::toString()
{
  string suitString;
  string valueString;
  switch(suit)
  {
    case 1:
      suitString = "Spades";
      break;
    case 2:
      suitString = "Hearts";
      break;
    case 3:
      suitString = "Diamonds";
      break;
    case 4:
      suitString = "Clubs";
      break;
  }
  switch(value)
  {
    case 2:
      valueString = "Duece";
      break;
    case 3:
      valueString = "Tres";
      break;
    case 4:
      valueString = "Four";
      break;
    case 5:
      valueString = "Five";
      break;
    case 6:
      valueString = "Six";
      break;
    case 7:
      valueString = "Seven";
      break;
    case 8:
      valueString = "Eight";
      break;
    case 9:
      valueString = "Nine";
      break;
    case 10:
      valueString = "Ten";
      break;
    case 11:
      valueString = "Jack";
      break;
    case 12:
      valueString = "Queen";
      break;
    case 13:
      valueString = "King";
      break;
    case 14:
      valueString = "Ace";
      break;
  }
  return valueString + " of " + suitString;
}

/* getValueString */
//Returns just the value of the string
string Card::getValueString()
{
  switch(value)
  {
    case 2:
      return "Deuce";
    case 3:
      return "Trey";
    case 4:
      return "Four";
    case 5:
      return "Five";
    case 6:
      return "Six";
    case 7:
      return "Seven";
    case 8:
      return "Eight";
    case 9:
      return "Nine";
    case 10:
      return "Ten";
    case 11:
      return "Jack";
    case 12:
      return "Queen";
    case 13:
      return "King";
    case 14:
      return "Ace";
    default:
      return "Error!";
  }
}