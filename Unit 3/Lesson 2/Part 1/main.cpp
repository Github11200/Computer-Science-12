#include "util.h"

int main()
{
  setSeed(4865431);
  int randomNumber = randInt(1, 100);

  int guess = 0;
  while (true)
  {
    guess = readInt(1, 100, "Guess a number between 1 and 100: ", "That is not between 1 and 100! Guess again: ");
    if (guess > randomNumber)
      cout << "Lower!" << endl;
    else if (guess < randomNumber)
      cout << "Higher!" << endl;
    else
    {
      cout << "Congratulations! You guessed the number!" << endl;
      break;
    }
  }

  return 0;
}