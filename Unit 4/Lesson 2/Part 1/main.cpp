#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void emptyStack(stack<string> &stackToEmpty)
{
  while (!stackToEmpty.empty())
    stackToEmpty.pop();
}

int main()
{
  stack<string> sitesBackward;
  stack<string> sitesForward;

  int option = 0;
  string site;
  while (true)
  {
    cout << endl;
    cout << "Would you like to: " << endl;
    cout << "1 - Go to a new site" << endl;
    cout << "2 - Go Back" << endl;
    cout << "3 - Go Forward" << endl;
    cout << "4 - Exit" << endl;
    cout << ">> ";
    cin >> option;

    if (option == 1)
    {
      cout << "Enter the new site to browse: ";
      cin >> site;
      sitesBackward.push(site);
      emptyStack(sitesForward);
      cout << "You are currently browsing " << site << endl;
    }
    else if (option == 2)
    {
      if (sitesBackward.size() == 1 || sitesBackward.empty())
        cout << "You do not have any history" << endl;
      else
      {
        sitesForward.push(sitesBackward.top());
        sitesBackward.pop();
        cout << "You are current browsing " << sitesBackward.top() << endl;
      }
    }
    else if (option == 3)
    {
      if (sitesForward.empty())
        cout << "You do not have any history" << endl;
      else
      {
        cout << "You are currently browsing " << sitesForward.top() << endl;
        sitesForward.pop();
      }
    }
    else
      break;
  }

  return 0;
}