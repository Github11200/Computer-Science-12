#include <vector>
#include <queue>
#include <algorithm>
#include <sstream>
#include <iostream>

using namespace std;

int readInt(const string prompt, string reprompt)
{
  if (reprompt == "")
    reprompt = prompt;

  int value = 0;
  cout << prompt;
  while (true)
  {
    string line;
    try
    {
      if (!getline(cin, line))
      {
        throw "getInteger: End of input reached while waiting for integer value.";
      }
    }
    catch (const char *c)
    {
      cerr << c << endl;
      exit(EXIT_FAILURE);
    }

    istringstream stream(line);
    stream >> value;
    if (!stream.fail() && stream.eof())
    {
      break;
    }

    cout << reprompt;
  }
  return value;
}

int main()
{
  int totalCustomers = readInt("How many customers do you want to simulate? ", "");
  int time = 1;

  /* Sim  2:
   * New customer every 5 ticks
   * Individual Qs
   * Customer always chooses the shortest
   * line (checking cashier 1, then 2, then 3)
   * cashier 1 - every 12 ticks
   * cashier 2 - every 19 ticks
   * cashier 3 - every 25 ticks
   *
   * How long does it take to check out
   * all customers?
   */

  int customerNumber = 2;
  queue<int> cashier1, cashier2, cashier3;

  queue<int> customers;
  customers.push(1);

  while (!customers.empty() || !cashier1.empty() || !cashier2.empty() || !cashier3.empty())
  {
    if (time % 5 == 0 && customerNumber <= totalCustomers)
      customers.push(customerNumber++);

    if (!cashier1.empty() && time % 12 == 0)
    {
      cout << "Cashier 1 served customer " << cashier1.front() << endl;
      cashier1.pop();
    }
    if (!cashier2.empty() && time % 19 == 0)
    {
      cout << "Cashier 2 served customer " << cashier2.front() << endl;
      cashier2.pop();
    }
    if (!cashier3.empty() && time % 25 == 0)
    {
      cout << "Cashier 3 served customer " << cashier3.front() << endl;
      cashier3.pop();
    }

    if (!customers.empty())
    {
      if (cashier1.size() <= cashier2.size() && cashier1.size() <= cashier3.size())
        cashier1.push(customers.front());
      else if (cashier2.size() < cashier1.size() && cashier2.size() <= cashier3.size())
        cashier2.push(customers.front());
      else
        cashier3.push(customers.front());
      customers.pop();
    }
    ++time;
  }

  cout << "It took a total of " << time << " ticks to serve all customers." << endl;

  return 0;
}