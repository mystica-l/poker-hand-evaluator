#include "Card.h"
#include "Constants.h"
#include "HandEvaluator.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

/* validCard */
//Takes in a string and a referenceCard and determines if the string card is valid
//Determines if it's in the right format and whether or not it's been already used, and then sets the card passed in by reference to the card object equivalent
bool validCard(string input, Card &referenceCard)
{
  string valueStringArray[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"};
  string suitStringArray[4] = {"s", "h", "c", "d"};
  static vector<string> stringCards;
  static bool firstRun = true;

  if(firstRun)
  {
    for(int i = 0; i < 13; i ++)
    { 
      for(int j = 0; j < 4; j ++)
      {
        string card = "";
        card += valueStringArray[i];
        card += suitStringArray[j];
        stringCards.push_back(card);
      }
    }
    firstRun = false;
  }
  
  bool validFormat = false;
  for(int i = 0; i < 52; i ++)
  {
    if(stringCards[i] == input)
    {
      validFormat = true;
    }
  }

  if(!validFormat)
  {
    cout << "The input was not in a valid format. (2s, Tc, Jd, Ah)" << endl;
    return false;
  }

  static vector<string> alreadyUsed;

  for(int i = 0; i < static_cast<int>(alreadyUsed.size()); i ++)
  {
    if(input == alreadyUsed[i])
    {
      cout << "This card has already been used." << endl;
      return false;
    }
  }
  alreadyUsed.push_back(input);

  Value inputValue;
  Suit inputSuit;
  switch(input[0])
  {
    case '2':
      inputValue = TWO;
      break;
    case '3':
      inputValue = THREE;
      break;
    case '4':
      inputValue = FOUR;
      break;
    case '5':
      inputValue = FIVE;
      break;
    case '6':
      inputValue = SIX;
      break;
    case '7':
      inputValue = SEVEN;
      break;
    case '8':
      inputValue = EIGHT;
      break;
    case '9':
      inputValue = NINE;
      break;
    case 'T':
      inputValue = TEN;
      break;
    case 'J':
      inputValue = JACK;
      break;
    case 'Q':
      inputValue = QUEEN;
      break;
    case 'K':
      inputValue = KING;
      break;
    case 'A':
      inputValue = ACE;
      break;
    default:
      cout << "Invalid card value" << endl;
      return false;
  }
  switch(input[1])
  {
    case 's':
      inputSuit = SPADES;
      break;
    case 'h':
      inputSuit = HEARTS;
      break;
    case 'c':
      inputSuit = CLUBS;
      break;
    case 'd':
      inputSuit = DIAMONDS;
      break;
    default:
      inputSuit = SPADES;
  }
  Card inputCard = Card(inputSuit, inputValue);
  referenceCard = inputCard;
  return true;
}

/* validPlayers */
//Takes in a string input for the number of players and validates that it's a number between 1 and 10
bool validPlayers(string input)
{
  if(input.length() == 0)
  {
    cout << "Please input just a number for how many players there are (1 - 10): ";
    return false;
  }
  for(int i = 0; i < static_cast<int>(input.length()); ++i)
  {
    if(!isdigit(input[i]))
    {
      cout << "Please input just a number for how many players there are (1 - 10): ";
      return false;
    }
  }
  int inputToInt = stoi(input);
  if(inputToInt > 10 || inputToInt < 1)
  {
    cout << "Please input just a number for how many players there are (1 - 10): ";
    return false;
  }
  return true;
}

/* main */
int main()
{
  cout << "Poker Hand Evaluator" << endl;
  cout << "This program lets you input several players' hands and a set of community cards to be evaluated!" << endl;
  cout << "The program will print out each player's hand ranking as well as who won!" << endl;
  
  string numPlayers = "";
  cout << "How many players are there? (1 - 10): ";
  getline(cin, numPlayers);
  while(!validPlayers(numPlayers))
  {
    getline(cin, numPlayers);
  }
  
  int intNumPlayers = stoi(numPlayers);

  //Allocates memory for a 2d array of everyone's hand rankings and everyone's cards related to the number of players
  HandRankings** allHandRankings = new HandRankings*[intNumPlayers];
  Card ** playerHands = new Card*[intNumPlayers];

  //Iterates through each player and prompts for their 2 cards and stores it in playerHands
  for(int i = 1; i <= intNumPlayers; i ++)
  {
    string input;
    playerHands[i - 1] = new Card[2];
    cout << "What is player " << i << "'s first card?: ";
    getline(cin, input);
    Card temp;
    while(!validCard(input, temp))
    {
      cout << "What is player " << i << "'s first card?: ";
      getline(cin, input);
    }
    playerHands[i - 1][0] = temp;

    cout << "What is player " << i << "'s second card?: ";
    getline(cin, input);
    while(!validCard(input, temp))
    {
      cout << "What is player " << i << "'s second card?: ";
      getline(cin, input);
    }
    playerHands[i - 1][1] = temp;
  }
  
  //Prompts the user for which stage of community cards they are on and sets numOfCommunityCards accordingly
  string communityCardStage = "";
  cout << "Have you dealt the flop, turn, or river? (f/t/r): ";
  getline(cin, communityCardStage);
  while(communityCardStage != "f" && communityCardStage != "t" && communityCardStage != "r")
  {
    cout << "Please enter just the character \"f\", \"t\", or \"r\" for the flop, turn, or river: ";
    getline(cin, communityCardStage);
  }
  int numOfCommunityCards = 0;
  if(communityCardStage == "f")
  {
    numOfCommunityCards = 3;
  }
  else if(communityCardStage == "t")
  {
    numOfCommunityCards = 4;
  }
  else
  {
    numOfCommunityCards = 5;
  }

  //Allocates memory for a dynamically sized array of community cards and prompts user for all of them
  Card * communityCards = new Card[numOfCommunityCards];
  
  for(int i = 1; i <= numOfCommunityCards; i ++)
  {
    string input;
    cout << "What is community card " << i << "?: ";
    getline(cin, input);
    Card temp;
    while(!validCard(input, temp))
    {
      cout << "What is community card " << i << "?: ";
      getline(cin, input);
    }
    communityCards[i - 1] = temp;
  }

  //Iterates through each player and creates a dynamically sized array storing
  //both the community cards and each player's hands and evaluates their hand before printing it out
  HandEvaluator handEvaluator;
  Card * communityAndPlayers = new Card[numOfCommunityCards + 2];
  for(int i = 1; i <= intNumPlayers; i ++)
  {
    for(int j = 0; j < 2; j ++)
    {
      communityAndPlayers[j] = playerHands[i - 1][j];
    }
    for(int j = 2; j < numOfCommunityCards + 2; j ++)
    {
      communityAndPlayers[j] = communityCards[j - 2];
    }
    allHandRankings[i - 1] = new HandRankings[6] {NULLRANK, NULLRANK, NULLRANK, NULLRANK, NULLRANK, NULLRANK};
    cout << "Player " << i << "'s Hand: ";
    handEvaluator.evaluateHand(communityAndPlayers, allHandRankings[i - 1], numOfCommunityCards + 2);
    handEvaluator.printHand(allHandRankings[i - 1]);
  }

  delete [] communityAndPlayers;
  delete [] communityCards;

  for(int i = 0; i < intNumPlayers; i ++)
  {
    delete [] allHandRankings[i];
    delete [] playerHands[i];
  }
  
  delete [] allHandRankings;
  delete [] playerHands;
}