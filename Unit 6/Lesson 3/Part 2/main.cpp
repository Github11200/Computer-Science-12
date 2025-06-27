#include <fstream>
#include <vector>
#include "util.h"

const int BEST_VALUE = 700;
const int MAX_WEIGHT = 50;

struct item
{
  string name;
  int value, weight;
  bool included;
};

vector<item> readContents()
{

  vector<item> output;
  ifstream in;
  in.open("contents.txt");
  if (in.fail())
    cout << "File didn't open" << endl;

  string line;
  while (true)
  {
    getline(in, line);
    if (in.fail())
      break; // will fail at end of file

    vector<string> split = splitLine(line);
    item newItem;
    newItem.name = split[0];
    newItem.value = stoi(split[1]);
    newItem.weight = stoi(split[2]);
    newItem.included = false;
    output.push_back(newItem);
  }
  return output;
}

void printItem(item i)
{
  cout << i.name << endl;
  cout << "Value: " << i.value << endl;
  cout << "Weight: " << i.weight << endl;
  cout << endl;
}

// Enter your recursive function here
bool airFreightHelper(vector<item> &items, int value, int weight)
{
  if (value >= 700)
    return true;
  else if (weight == 50 && value < 700)
    return false;

  for (int i = 0; i < items.size(); ++i)
  {
    if (!items[i].included && weight + items[i].weight <= 50)
    {
      items[i].included = true;
      if (airFreightHelper(items, value + items[i].value, weight + items[i].weight))
        return true;
      items[i].included = false;
    }
  }
}

// Use this function to kick off your recursive call
void airFreight(vector<item> &items)
{
  airFreightHelper(items, 0, 0);
}

int main()
{

  vector<item> items = readContents();

  // Call your recursive function
  airFreight(items);

  // Print out the results
  int totalValue = 0, totalWeight = 0;
  for (int i = 0; i < items.size(); ++i)
  {
    if (items[i].included)
    {
      cout << items[i].name << endl;
      cout << "Value: " << items[i].value << endl;
      cout << "Weight: " << items[i].weight << endl;
      cout << endl;

      totalValue += items[i].value;
      totalWeight += items[i].weight;
    }
  }

  cout << "Total Value: " << totalValue << endl;
  cout << "Total Weight: " << totalWeight << endl;

  return 0;
}
