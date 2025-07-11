#include <vector>
#include <map>
#include <cmath> // used for the sqrt function
#include <iostream>
#include <sstream>
#include <ctime>

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

// Cell tower struct
struct cellTower
{
  int x, y;
};

const int GRID_SIZE = 10;
const double FREQ_DISTANCE = 5.6;
const double TOWER_DISTANCE = 2.1;
//  The FREQ vector  may have more frequencies than needed
const vector<char> FREQ{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};

// Helper function to print grid
void printGrid(vector<vector<char>> grid)
{
  for (int row = 0; row < GRID_SIZE; row++)
  {
    for (int col = 0; col < GRID_SIZE; col++)
    {
      cout << grid[row][col] << ' ';
    }
    cout << endl;
  }
}

// Helper function to determine the distance between points.
// x and y should represent the grid coordinates.
double distance(int x1, int y1, int x2, int y2)
{
  int a = x2 - x1;
  int b = y2 - y1;
  return sqrt(a * a + b * b);
}
// Helper function to determine if a tower is needed
// Returns true if distance of point is less than TOWER_DISTANCE
bool towerNeeded(vector<vector<char>> grid, int testRow, int testCol)
{
  for (int i = 0; i < grid.size(); ++i)
  {
    for (int j = 0; j < grid[i].size(); ++j)
    {
      if (grid[i][j] != '.' && distance(j, i, testCol, testRow) < TOWER_DISTANCE)
        return false;
    }
  }
  return true;
}

// Helper function to find the next valid frequency
// Returns the next frequency to use
char validFreq(vector<vector<char>> grid, int testRow, int testCol, int numFreq)
{
  map<char, char> frequencies;
  for (int i = 0; i < numFreq; ++i)
    frequencies.insert({FREQ[i], '.'});
  for (int i = 0; i < grid.size(); ++i)
  {
    for (int j = 0; j < grid[i].size(); ++j)
    {
      if ((i == testRow && j == testCol) || grid[i][j] == '.')
        continue;
      if (distance(j, i, testCol, testRow) < FREQ_DISTANCE)
        frequencies.erase(grid[i][j]);
    }
  }
  if (frequencies.empty())
    return '.';
  return frequencies.begin()->first;
}

// Solver recursive function.
bool cellSolver(vector<vector<char>> &grid, int row, int col, int numFreq)
{
  if (row == grid.size())
    return true;
  else if (col == grid.size())
    return cellSolver(grid, row + 1, 0, numFreq);
  else if (grid[row][col] != '.')
    return cellSolver(grid, row, col + 1, numFreq);

  for (int rowToTry = 0; rowToTry < grid.size(); ++rowToTry)
  {
    for (int columnToTry = 0; columnToTry < grid.size(); ++columnToTry)
    {
      if (towerNeeded(grid, rowToTry, columnToTry))
      {
        char frequency = validFreq(grid, rowToTry, columnToTry, numFreq);
        if (frequency == '.')
          return false;
        grid[rowToTry][columnToTry] = frequency;
        if (cellSolver(grid, rowToTry, columnToTry + 1, numFreq))
          return true;
        grid[rowToTry][columnToTry] = '.';
      }
    }
  }

  return false;
}

// Helper function to kick off problem
bool cellProblem(vector<vector<char>> &grid, int numFreq)
{
  return cellSolver(grid, 0, 0, numFreq);
}

int main()
{
  // Create the empty grid of size GRID_SIZE.
  // Place a '.' in each square
  vector<vector<char>> grid;
  for (int i = 0; i < GRID_SIZE; ++i)
  {
    vector<char> temp;
    for (int j = 0; j < GRID_SIZE; ++j)
      temp.push_back('.');
    grid.push_back(temp);
  }

  // grid[0][0] = 'a';

  // Prompt the user for the number of frequecies
  int numberOfFrequencies = readInt("Please select the number of frequencies to test (1 - 10): ", "");
  bool isPossible = cellProblem(grid, numberOfFrequencies);

  // Print the results
  if (!isPossible)
    cout << "No Solution possible." << endl;
  else
    printGrid(grid);

  return 0;
}