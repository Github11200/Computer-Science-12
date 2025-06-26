#include "util.h"
#include <stack>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
  string filename;

  cout << "Please enter a file to check: ";
  cin >> filename;

  ifstream input;
  input.open(filename);

  if (input.fail())
  {
    cout << "Could not open the file." << endl;
    return -1;
  }

  stack<char> brackets;
  string line;
  int lineNumber = 1;
  while (true)
  {
    getline(input, line);
    if (input.fail())
      break;

    for (char letter : line)
    {
      if (letter == '(')
        brackets.push(')');
      else if (letter == '{')
        brackets.push('}');
      else if (letter == '[')
        brackets.push(']');
      else if (!brackets.empty() && letter == brackets.top())
        brackets.pop();
      else if (!brackets.empty() && (letter == ')' || letter == '}' || letter == ']') && letter != brackets.top())
        Error("Line: " + to_string(lineNumber) + " Expecting " + brackets.top() + " but found " + letter);
    }
    ++lineNumber;
  }

  if (!brackets.empty())
    Error("Brackets do not match up.");
  cout << "Your code looks good!" << endl;

  return 0;
}