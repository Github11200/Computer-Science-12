#include "util.h"
#include <vector>
#include <map>
#include <fstream>

int main()
{
  string filename;
  cout << "Please enter the file name: ";
  cin >> filename;

  ifstream input;
  input.open(filename);
  if (input.fail())
  {
    cout << "Could not open the file." << endl;
    return -1;
  }

  map<string, int> wordCount;
  string line;
  while (true)
  {
    getline(input, line);
    if (input.fail())
      break;

    vector<string> words = splitLine(line, ' ');
    for (string word : words)
    {
      word = toLowerCase(word);
      wordCount[word]++;
    }
  }

  map<string, int>::iterator wordCountIterator = wordCount.begin();
  for (; wordCountIterator != wordCount.end(); ++wordCountIterator)
    if (wordCountIterator->second > 100)
      cout << wordCountIterator->first << ": " << wordCountIterator->second << endl;

  return 0;
}
