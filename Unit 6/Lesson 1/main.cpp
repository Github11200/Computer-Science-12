#include <iostream>
#include <math.h>
#include <string>

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
  int validPair = 0;
  if ((sequence1[0] == 'A' && sequence2[0] == 'T') || (sequence1[0] == 'T' && sequence2[0] == 'A'))
    validPair = 1;
  else if ((sequence1[0] == 'G' && sequence2[0] == 'C') || (sequence1[0] == 'C' && sequence2[0] == 'G'))
    validPair = 1;
  return validPair + validDNASequences(sequence1.substr(1, sequence1.size() - 1), sequence2.substr(1, sequence2.size() - 1));
}

bool containsSubsequence(string str, string subsequence)
{
  if (subsequence.size() == 0)
    return true;
  else if (str.size() == 0)
    return false;

  return containsSubsequence(str.substr(1, str.size() - 1), (str[0] == subsequence[0] ? subsequence.substr(1, subsequence.size() - 1) : subsequence));
}

int main()
{
  return 0;
}