#include <iostream>
#include <stdio.h>
#include <string>
#include <queue>

using namespace std;

int main()
{
  queue<int> q;
  q.push(1);
  q.push(2);
  int num = q.front();
  q.pop();
  q.push(num);
  q.push(3);
  q.pop();

  cout << num << endl;

  return 0;
}