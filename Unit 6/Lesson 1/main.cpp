#include <iostream>
#include <math.h>

using namespace std;

int sumDigits(int num)
{
  if (to_string(num).size() == 1)
    return num;
  int divisor = static_cast<int>(pow(10, to_string(num).size() - 1));
  return (num / divisor) + sumDigits(num % divisor);
}

string removeALetter(string input)
{
  if (input.size() == 1)
    return (input[0] == 'A' ? "" : input);
  string firstPart = (input[0] == 'A' ? "" : input.substr(0, 1));
  string secondPart = removeALetter(input.substr(1, input.size() - 1));
  return firstPart + secondPart;
}

int validDNASequences(string sequence1, string sequence2)
{
  if (sequence1.size() == 0 || sequence2.size() == 0)
    return 0;
}

int main()
{
  string phrase;
  cin >> phrase;
  cout << removeALetter(phrase) << endl;

  return 0;
}