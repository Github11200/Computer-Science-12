#include "util.h"
#include <vector>

/* This function will print your triangle. Call it
 * from your base case. It should not be altered.
 */

void printTriangle(vector<vector<int>> &t)
{
  int size = t.size();
  if (size % 2 == 1)
  {
    size--;
  }
  for (int i = 0; i < t.size(); i++)
  {
    for (int j = 0; j < (size - i) / 2; j++)
    {
      cout << "\t";
    }
    for (int item : t[i])
    {
      if (i % 2 == 1)
      {
        cout << "   ";
      }
      cout << item << "\t";
    }
    cout << endl;
  }
}

/* This will be your recursive function. */
void pascalRec(vector<vector<int>> &t, int remain)
{
  if (remain == 0)
  {
    printTriangle(t);
    return;
  }

  vector<int> row{1};
  int currentLevel = t.size() + 1;
  for (int i = 1; i < currentLevel - 1; ++i)
    row.push_back(t[currentLevel - 2][i - 1] + t[currentLevel - 2][i]);
  row.push_back(1);
  t.push_back(row);

  pascalRec(t, remain - 1);
}

/* This is your helper function. It is set up
 * to create the first row of the Pascal
 * triangle and then call the recursive function.
 * It should not be altered.
 */
void pascal(int levels)
{
  vector<vector<int>> triangle{{1}};
  pascalRec(triangle, levels - 1);
}

int main()
{
  return 0;
}
