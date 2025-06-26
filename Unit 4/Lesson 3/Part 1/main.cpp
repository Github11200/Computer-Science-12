#include "util.h"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int main()
{
  int totalCustomers = readInt("How many customers do you want to simulate? ", "");
  int time = 1;

  /* Sim  1:
   * New customer every 5 ticks
   * Central queue
   * cashier 1 - every 12 ticks
   * cashier 2 - every 19 ticks
   * cashier 3 - every 25 ticks
   *
   * How long does it take to check out
   * all customers?
   */

  queue<int> customers;
  customers.push(1);
  int customerNumber = 2;

  while (!customers.empty())
  {
    if (time % 5 == 0 && customerNumber <= totalCustomers)
      customers.push(customerNumber++);

    if (!customers.empty() && time % 12 == 0)
    {
      cout << "Cashier 1 served customer " << customers.front() << endl;
      customers.pop();
    }
    if (!customers.empty() && time % 19 == 0)
    {
      cout << "Cashier 2 served customer " << customers.front() << endl;
      customers.pop();
    }
    if (!customers.empty() && time % 25 == 0)
    {
      cout << "Cashier 3 served customer " << customers.front() << endl;
      customers.pop();
    }
    ++time;
  }

  cout << "It took a toal of " << time << " ticks to serve all customers." << endl;

  return 0;
}