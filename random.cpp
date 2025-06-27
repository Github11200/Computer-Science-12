#include <iostream>
#include <stdio.h>
#include <string>
#include <queue>
#include <map>

using namespace std;

void mystery(int num)
{
  if (num <= 2)
  {
    cout << num;
  }
  else
  {
    if (num % 2 == 0)
    {
      mystery(num / 2);
    }
    else
    {
      mystery((num + 1) / 2);
      mystery((num - 1) / 2);
    }
  }
}

int main()
{
  mystery(9);

  return 0;
}