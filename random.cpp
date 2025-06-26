#include <iostream>
#include <stdio.h>
#include <string>
#include <queue>
#include <map>

using namespace std;

int main()
{
  map<string, int> age{{"Karel", 9}, {"Tracy", 5}};

  age.insert(pair<string, double>("Karel", 10));

  cout << age["Karel"] << endl;

  return 0;
}