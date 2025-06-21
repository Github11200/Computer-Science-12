#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

void printStar()
{
  cout << "*";
}
void printSpace()
{
  cout << " ";
}

void printTriangle(int size)
{
  int numberOfSpaces = (size * 2 - 1) / 2;
  int numberOfAstrixes = 1;

  for (int i = 0; i < size; ++i)
  {
    for (int j = 0; j < numberOfSpaces; ++j)
      printSpace();
    for (int j = 0; j < numberOfAstrixes; ++j)
      printStar();
    numberOfAstrixes += 2;
    --numberOfSpaces;
    cout << endl;
  }
}

void drawingATriangle()
{
  int size;
  cout << "Please enter the size of your triangle: ";
  cin >> size;

  while (size >= 10 || size <= 0)
  {
    cout << "Invalid input, please try again: ";
    cin >> size;
  }

  printTriangle(size);
}

string inputLine(string prompt)
{
  string input;
  cout << prompt;
  getline(cin, input);
  return input;
}

double inputDouble(string prompt)
{
  double input;
  cout << prompt;
  cin >> input;
  return input;
}

double inputDouble(string prompt, double min, double max)
{
  double input = inputDouble(prompt);
  while (input < min || input > max)
    input = inputDouble(prompt);
  return input;
}

int inputInt(string prompt)
{
  int input;
  cout << prompt;
  cin >> input;
  return input;
}

int inputInt(string prompt, int min, int max)
{
  int input = inputInt(prompt);
  while (input < min || input > max)
    input = inputInt(prompt);
  return input;
}

void easierInput()
{
  string stringInput = inputLine("Please enter a string: ");
  cout << "You entered: " << stringInput << endl;

  double doubleInput = inputDouble("Please enter a double: ");
  cout << "You entered: " << doubleInput << endl;

  double constrainedDoubleInput = inputDouble("Please enter a double between 0 and 1: ", 0, 1);
  cout << "You entered: " << constrainedDoubleInput << endl;

  int intInput = inputInt("Please enter an int: ");
  cout << "You entered: " << intInput << endl;

  int constrainedIntInput = inputInt("Please enter an int between 0 and 10: ", 0, 10);
  cout << "You entered: " << constrainedIntInput << endl;
}

void stringToUppercase(string &input)
{
  for (int i = 0; i < input.length(); ++i)
    input[i] = toupper(input[i]);
}

void encrypt(string &input, int shiftValue)
{
  for (int i = 0; i < input.length(); ++i)
  {
    int ascii = int(input[i]);
    ascii += shiftValue;
    if (ascii > 90)
      ascii = 64 + (ascii - 90);
    input[i] = static_cast<char>(ascii);
  }
}

void decrypt(string &input, int shiftValue)
{
  for (int i = 0; i < input.length(); ++i)
  {
    int ascii = int(input[i]);
    ascii -= shiftValue;
    if (ascii < 65)
      ascii = 91 - (65 - ascii);
    input[i] = static_cast<char>(ascii);
  }
}

void encryption()
{
  string phrase = inputLine("Enter a phrase: ");
  bool encryptOrDecrypt = inputLine("Would you like to (e)ncrypt or (d)ecrypt? ") == "e" ? true : false;
  int shiftValue = inputInt("How much would you like to shift (1-26)? ");

  stringToUppercase(phrase);

  if (encryptOrDecrypt)
    encrypt(phrase, shiftValue);
  else
    decrypt(phrase, shiftValue);

  cout << (encryptOrDecrypt ? "Your encrypted word: " : "Your decrypted word: ") << phrase << endl;
}

int main()
{
  return 0;
}
