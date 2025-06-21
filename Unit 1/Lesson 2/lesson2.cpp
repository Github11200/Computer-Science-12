#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

void holeInOne()
{
  string firstString, secondString;

  cout << "Please enter your first string: ";
  getline(cin, firstString);

  cout << "Please enter your second string: ";
  getline(cin, secondString);

  secondString.insert(secondString.length() / 2, firstString);
  cout << secondString << endl;
}

void looseChange()
{
  int numberOfCents;

  cout << "Please enter an amount (less than 1000 cents): ";
  cin >> numberOfCents;

  cout << "Quarters: " << numberOfCents / 25 << endl;
  numberOfCents %= 25;

  cout << "Dimes: " << numberOfCents / 10 << endl;
  numberOfCents %= 10;

  cout << "Nickels: " << numberOfCents / 5 << endl;
  numberOfCents %= 5;

  cout << "Pennies: " << numberOfCents << endl;
}

void fastFood()
{
  int numberOfChickenSandwiches, numberOfWaffleFries, numberOfSodas;

  cout << "Please enter the number of Chicken Sandwiches: ";
  cin >> numberOfChickenSandwiches;

  cout << "Please enter the number of Waffle Fries: ";
  cin >> numberOfWaffleFries;

  cout << "Please enter the number of Sodas: ";
  cin >> numberOfSodas;

  cout << endl;

  double subtotal = (3.90 * numberOfChickenSandwiches) + (2.20 * numberOfWaffleFries) + (1.60 * numberOfSodas);
  double tax = 0.1 * subtotal;
  double total = subtotal + tax;

  cout << "Subtotal: $" << subtotal << endl;
  cout << "Tax: $" << tax << endl;
  cout << "Total: $" << total << endl;
}

int main()
{
  return 0;
}
