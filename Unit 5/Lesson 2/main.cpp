#include <set>
#include <iostream>
#include <string>

using namespace std;

int main()
{
  set<int> visitedTeams;
  int option = 0;
  while (true)
  {
    cout << "Please select an option:" << endl;
    cout << "1. Add a team" << endl;
    cout << "2. List all teams" << endl;
    cout << "3. Exit" << endl;
    cout << ">> ";
    cin >> option;

    if (option == 3)
      break;
    else if (option == 1)
    {
      int number;
      cout << "Enter a team number: ";
      cin >> number;
      if (visitedTeams.insert(number).second)
        cout << "Added team " << number << endl;
      else
        cout << "You already visited team " << number << endl;
    }
    else
    {
      set<int>::iterator visitedTeamsIterator = visitedTeams.begin();
      cout << "Teams visited:" << endl;
      for (; visitedTeamsIterator != visitedTeams.end(); ++visitedTeamsIterator)
        cout << *visitedTeamsIterator << endl;
    }
  }

  return 0;
}