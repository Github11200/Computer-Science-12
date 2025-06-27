#include "util.h"
#include <fstream>
#include <vector>
#include <set>

using namespace std;

set<string> words;

vector<vector<char>> letters{
    {}, {}, {'A', 'B', 'C'}, {'D', 'E', 'F'}, {'G', 'H', 'I'}, {'J', 'K', 'L'}, {'M', 'N', 'O'}, {'P', 'Q', 'R', 'S'}, {'T', 'U', 'V'}, {'W', 'X', 'Y', 'Z'}};

void loadDict()
{
  ifstream in;
  in.open("words.txt");
  string word;
  while (true)
  {
    getline(in, word);
    if (in.fail())
      break;
    words.insert(word);
  }
}

// Write your recursive function here
void phoneWords(vector<string> &wordsFound, string number, string word)
{
  if (number.size() == 0)
  {
    wordsFound.push_back(word);
    return;
  }

  if (number[0] == '0' || number[0] == 1)
    phoneWords(wordsFound, number.substr(1, number.size() - 1), word);
  else
    for (char character : letters[number[0] - '0'])
      phoneWords(wordsFound, number.substr(1, number.size() - 1), word + string{character});
}

int main()
{
  loadDict();

  int phoneNumber = readInt("Please enter a phone number: ", "");

  // Call your recursive method
  vector<string> possibleWords;
  phoneWords(possibleWords, to_string(phoneNumber), "");

  for (string word : possibleWords)
    if (words.find(word) != words.end())
      cout << word << endl;

  cout << "End of List" << endl;

  return 0;
}
