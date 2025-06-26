#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <queue>

using namespace std;

vector<pair<string, char>> makeDeck()
{
  vector<pair<string, char>> cards;
  vector<char> suits{'D', 'C', 'H', 'S'};
  vector<string> values{"A", "K", "Q", "J", "10", "9", "8", "7", "6", "5", "4", "3", "2"};

  for (int i = 0; i < values.size(); ++i)
    for (int j = 0; j < suits.size(); ++j)
      cards.push_back(pair<string, char>(values[i], suits[j]));
  return cards;
}

queue<pair<string, char>> shuffle(vector<pair<string, char>> deck)
{
  queue<pair<string, char>> cardsQueue;

  while (!deck.empty())
  {
    int randomIndex = rand() % deck.size();
    cardsQueue.push(deck[randomIndex]);

    vector<pair<string, char>>::iterator deckIterator = deck.begin();
    deck.erase(deckIterator + randomIndex);
  }

  return cardsQueue;
}

int main()
{
  queue<pair<string, char>> deck = shuffle(makeDeck());
  for (int i = 0; i < 10; ++i)
  {
    cout << deck.front().first << " - " << deck.front().second << endl;
    deck.pop();
  }

  return 0;
}