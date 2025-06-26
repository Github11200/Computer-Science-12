#include <iostream>
#include <vector>

using namespace std;

int main()
{
  int width, height, seedValue, stepValue;

  cout << "Please enter a width: ";
  cin >> width;
  cout << "Please enter a height: ";
  cin >> height;
  cout << "Please enter a seed value: ";
  cin >> seedValue;
  cout << "Please enter a step value: ";
  cin >> stepValue;

  for (int i = 0; i < height; ++i)
  {
    for (int j = 0; j < width; ++j)
      cout << (seedValue + (stepValue * j)) << "\t";
    cout << endl;
    seedValue += stepValue;
  }

  return 0;
}