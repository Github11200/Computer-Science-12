#include <vector>
#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Global variables
int boardSize = 0;

// 0 -> Empty
// 1 -> Player - O
// 2 -> Computer - X
vector<vector<int>> board;

void drawDashes()
{
  for (int j = 0; j < board.size(); ++j)
    cout << "----";
  cout << "-";
}

void drawBoard()
{
  system("clear");
  for (int i = 0; i < board.size(); ++i)
  {
    if (i == 0)
    {
      drawDashes();
      cout << endl;
    }

    for (int j = 0; j < board[i].size(); ++j)
    {
      if (j == 0)
        cout << "|";

      if (board[i][j] == 0)
        cout << "   ";
      else if (board[i][j] == 1)
        cout << " O ";
      else
        cout << " X ";

      cout << "|";
    }

    cout << endl;
    drawDashes();
    cout << endl;
  }
}

int intInputRange(string prompt, int min, int max)
{
  string stringInput;
  int input;
  bool isValid = false;

  cout << prompt;

  while (!isValid)
  {
    try
    {
      cin >> stringInput;
      input = stoi(stringInput);

      if (input < min)
        throw logic_error("The number is too small, please try again: ");
      if (input > max)
        throw logic_error("The number is too large, please try again: ");

      isValid = true;
    }
    catch (invalid_argument)
    {
      cout << "Invalid argument. Please enter a number: ";
    }
    catch (exception const &e)
    {
      cout << e.what();
    }
  }

  return input;
}

int countInEachRowColumnAndDiagonal(vector<vector<int>> &arr, int &numberOfO, int &numberOfX)
{
  // 0 means no winner, it's just neutral
  int winner = 0;

  for (int i = 0; i < arr.size(); ++i)
  {
    int tempOCount = 0;
    int tempXCount = 0;
    bool allO = false;
    bool allX = false;
    bool neutral = false;
    for (int j = 0; j < arr[i].size(); ++j)
    {
      if (arr[i][j] == 0)
        continue;
      else if (allX == false && allO == false)
      {
        if (arr[i][j] == 1)
        {
          allO = true;
          ++tempOCount;
        }
        else
        {
          allX = true;
          ++tempXCount;
        }
      }
      else if ((arr[i][j] == 1 && allX) || (arr[i][j] == 2 && allO))
      {
        neutral = true;
        break;
      }
      else if (allO)
        ++tempOCount;
      else
        ++tempXCount;
    }

    if (!neutral)
    {
      numberOfO += tempOCount;
      numberOfX += tempXCount;
      if (tempOCount == boardSize)
        winner = 1; // 1 means the user playing won
      else if (tempXCount == boardSize)
        winner = -1; // -1 means the computer won
    }
  }

  return winner;
}

int staticEvaluation(vector<vector<int>> currentBoard)
{
  // Loop through each row, column and then the 2 diagonals
  // Check If the row has only O's or only X's and if it does have only one of those then count how many
  // Repeat this for everything, tallying it up, remember to convert the X's to a negative number before adding the two together

  // The computer is the MINIMIZER
  // The player is the MAXIMIZER

  // Return 0 if it is neutral
  // Return 1 if the user won
  // Return -1 if the computer won

  int numberOfO = 0;
  int numberOfX = 0;
  int winner = 0;

  winner = winner == 0 ? countInEachRowColumnAndDiagonal(currentBoard, numberOfO, numberOfX) : winner;

  vector<vector<int>> boardColumns;
  for (int i = 0; i < currentBoard.size(); ++i)
  {
    vector<int> temp;
    for (int j = 0; j < currentBoard.size(); ++j)
      temp.push_back(currentBoard[j][i]);
    boardColumns.push_back(temp);
  }
  winner = winner == 0 ? countInEachRowColumnAndDiagonal(boardColumns, numberOfO, numberOfX) : winner;

  vector<vector<int>> boardDiagonals(2);
  for (int i = 0; i < currentBoard.size(); ++i)
  {
    boardDiagonals[0].push_back(currentBoard[i][i]);
    boardDiagonals[1].push_back(currentBoard[i][boardSize - i - 1]);
  }
  winner = winner == 0 ? countInEachRowColumnAndDiagonal(boardDiagonals, numberOfO, numberOfX) : winner;

  return winner;
}

int isGameOver(vector<vector<int>> currentBoard)
{
  if (staticEvaluation(currentBoard) != 0) // Someone won
    return true;
  else
  {
    for (int i = 0; i < currentBoard.size(); ++i)
      for (int j = 0; j < currentBoard[i].size(); ++j)
        if (currentBoard[i][j] == 0) // There is no winner and the board isn't completely full
          return false;
    return true; // The board is completely full but there isn't a winner
  }
}

pair<int, pair<int, int>> minimax(vector<vector<int>> currentBoard, int depth, int alpha, int beta, bool maximizingPlayer)
{
  if (depth == 0 || isGameOver(currentBoard))
    return pair<int, pair<int, int>>(staticEvaluation(currentBoard), pair<int, int>(-1, -1));
  if (maximizingPlayer)
  {
    int maxEvaluation = INT32_MIN;
    pair<int, int> maxEvaluationPosition = pair<int, int>(0, 0);
    int evaluation = 0;
    for (int i = 0; i < currentBoard.size(); ++i)
    {
      for (int j = 0; j < currentBoard[i].size(); ++j)
      {
        if (currentBoard[i][j] == 0)
        {
          currentBoard[i][j] = 1;
          evaluation = minimax(currentBoard, depth - 1, alpha, beta, false).first;

          if (evaluation > maxEvaluation)
          {
            maxEvaluation = evaluation;
            maxEvaluationPosition = pair<int, int>(i, j);
          }
          alpha = max(alpha, evaluation);
          // if (beta <= alpha)
          //   break;
          currentBoard[i][j] = 0;
        }
      }
    }
    return pair<int, pair<int, int>>(maxEvaluation, maxEvaluationPosition);
  }
  else
  {
    int minEvaluation = INT32_MAX;
    pair<int, int> minEvaluationPosition = pair<int, int>(0, 0);
    int evaluation = 0;

    for (int i = 0; i < currentBoard.size(); ++i)
    {
      for (int j = 0; j < currentBoard[i].size(); ++j)
      {
        if (currentBoard[i][j] == 0)
        {
          currentBoard[i][j] = 2;
          evaluation = minimax(currentBoard, depth - 1, alpha, beta, true).first;

          if (evaluation < minEvaluation)
          {
            minEvaluation = evaluation;
            minEvaluationPosition = pair<int, int>(i, j);
          }
          beta = max(beta, evaluation);
          // if (beta <= alpha)
          //   break;
          currentBoard[i][j] = 0;
        }
      }
    }
    return pair<int, pair<int, int>>(minEvaluation, minEvaluationPosition);
  }
}

int main()
{
  boardSize = intInputRange("Welcome! Please enter the board size you'd like (3 - 10): ", 3, 10);

  board.resize(boardSize);
  for (int i = 0; i < board.size(); ++i)
    board[i].resize(boardSize);

  int row = 0, column = 0;
  drawBoard();
  while (true)
  {
    row = intInputRange("Please select a row (1 - " + to_string(boardSize) + "): ", 1, boardSize);
    column = intInputRange("Please select a column (1 - " + to_string(boardSize) + "): ", 1, boardSize);

    board[row - 1][column - 1] = 1;
    drawBoard();

    if (isGameOver(board))
      break;

    pair<int, int> position = minimax(board, 15, INT32_MIN, INT32_MAX, false).second;
    board[position.first][position.second] = 2;
    drawBoard();

    if (isGameOver(board))
      break;
  }

  return 0;
}
