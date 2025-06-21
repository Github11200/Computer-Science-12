#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

void summingDigits()
{
  int number;
  cout << "Please enter a positive integer: ";
  cin >> number;
  cout << endl;

  string numberString = to_string(number);
  int sum = 0;
  for (int i = 0; i < numberString.length(); ++i)
    sum += numberString[i] - '0';
  cout << "The sum of the digits is " << sum << endl;
}

void hackerSpeak()
{
  string originalPhrase;
  cout << "Please enter your phrase: " << originalPhrase;
  getline(cin, originalPhrase);

  string newPhrase = originalPhrase;
  for (int i = 0; i < newPhrase.length(); ++i)
  {
    if (newPhrase[i] == 'a' || newPhrase[i] == 'A')
      newPhrase[i] = '4';
    else if (newPhrase[i] == 'e' || newPhrase[i] == 'E')
      newPhrase[i] = '3';
    else if (newPhrase[i] == 'i' || newPhrase[i] == 'I')
      newPhrase[i] = '1';
    else if (newPhrase[i] == 'o' || newPhrase[i] == 'O')
      newPhrase[i] = '0';
  }

  cout << originalPhrase << " in H4ck3r Sp34k: " << newPhrase << endl;
}

void theNecklaceProblem()
{
  int originalDigitOne, originalDigitTwo;

  cout << "Please enter two digits separated by a space: ";
  cin >> originalDigitOne >> originalDigitTwo;

  int digitOne = originalDigitOne;
  int digitTwo = originalDigitTwo;

  cout << originalDigitOne << " " << originalDigitTwo << " ";

  int temp;
  int numberOfSteps = 0;
  do
  {
    temp = to_string(digitOne + digitTwo)[to_string(digitOne + digitTwo).length() - 1] - '0';
    digitOne = digitTwo;
    digitTwo = temp;

    ++numberOfSteps;
    cout << digitTwo << " ";
  } while (!(digitOne == originalDigitOne && digitTwo == originalDigitTwo));

  cout
      << "\nTotal Steps: " << numberOfSteps << endl;
}

int main()
{
  return 0;
}
