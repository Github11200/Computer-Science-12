#include <iostream>
#include "upper.h"

using namespace std;

int main()
{
  cout << "Enter a phrase: ";
  string phrase;
  getline(cin, phrase);

  cout << "Converted to Uppercase: " << upperCase(phrase) << endl;
  return 0;
}