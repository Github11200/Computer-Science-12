#include <vector>
#include <iostream>
#include <string>
#include <limits>
#include <fstream>

using namespace std;

// Global variables
int boardSize = 0;
int numberOfTimesHumanWon = 0;
int numberOfTimesComputerWon = 0;
string FILENAME = "score.txt";

// 0 -> Empty
// 1 -> Player - O
// 2 -> Computer - X
vector<vector<int>> board;

/**
 * @brief Draw the dashses so you can display the board in the terminal
 */
void drawDashes()
{
  for (int j = 0; j < board.size(); ++j)
    cout << "----";
  cout << "-";
}

/**
 * @brief Draw's the entire board placing O's for the player and X's for the computer
 * -------------
 * |   |   |   |
 * -------------
 * |   |   |   |
 * -------------
 * |   |   |   |
 * -------------
 */
void drawBoard()
{
  system("clear");
  for (int i = 0; i < board.size(); ++i)
  {
    // You want to draw dashes at the very top, so if this is the first iteration then draw dashes there as well
    if (i == 0)
    {
      drawDashes();
      cout << endl;
    }

    // Print out the characters inside each box
    for (int j = 0; j < board[i].size(); ++j)
    {
      // Like the dashes, you want the pipes on the very lefthand side as well, so if it's the first iteration
      // then add it at the very start
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

/**
 * @brief Gets an integer input from the user within a certain range
 * @param prompt The prompt that is initially printed out
 * @param min The minimum integer value
 * @param max The maximum integer value
 * @return Return's the integer the user has entered, making sure it meets the requirements
 */
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
      input = stoi(stringInput); // Convert the number to an integer, if it doesn't work it will go into the invalid_argument catch block

      // Check if the number is within the rage
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

/**
 * @brief Counts how many O's or X's are in each row, column and diagonal and also returns a winner if there is one
 *
 * Ex. If a row contains 2 O's and no X's then it would add 2 to the number of O, but if there were
 * an X then it would add nothing since that row is then neutral (neither O nor X can win)
 *
 * @param arr You can pass in the rows, columns or diagonals here to be counted
 * @param numberOfO This is the number of O's there are
 * @param numberOfX This is the number of X's there are
 * @return If there is a winner found then it will return that, -1 means the computer won, 1 means the user won and 0 means no winner
 */
int countInEachRowColumnAndDiagonal(vector<vector<int>> &arr, int &numberOfO, int &numberOfX)
{
  // 0 means no winner, it's just neutral
  int winner = 0;

  for (int i = 0; i < arr.size(); ++i)
  {
    // These temporary variables are meant to hold the count in just the current row, column or diagonal
    int tempOCount = 0;
    int tempXCount = 0;

    // If the first character detected is an O then allO becomes true meaning that the whole array should
    // have just an O, but if there's an X then it means it's neutral and not counted. The same goes for X
    bool allO = false;
    bool allX = false;
    bool neutral = false;
    for (int j = 0; j < arr[i].size(); ++j)
    {
      if (arr[i][j] == 0) // If the square is empty then there's nothing to count
        continue;
      else if (allX == false && allO == false) // If allX or allO hasn't been assigned yet then do so, it just means that all the squares before this were empty
      {
        // If it's an O then the rest of the array should be an O, and the same goes for X
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
      // If you're looking for the whole array to be an O and you found an X instead, or vice versa, then that means the array is neutral and no points should be counted
      // If the row looked like this: | O | X |  | then neither O nor X should get incremented as neither one will win in this specific array
      else if ((arr[i][j] == 1 && allX) || (arr[i][j] == 2 && allO))
      {
        neutral = true;
        break;
      }
      // If the previous condition is not met it means that the current square has an O and it's all O and the same goes for X, so increment their respective counts
      else if (allO)
        ++tempOCount;
      else
        ++tempXCount;
    }

    // If the array hasn't been neutralized then update the counts
    if (!neutral)
    {
      numberOfO += tempOCount;
      numberOfX += tempXCount;

      // If the whole array had just O or just X it means that one of those won, so assign that to the winner
      if (tempOCount == boardSize)
        winner = 1; // 1 means the user playing won
      else if (tempXCount == boardSize)
        winner = -1; // -1 means the computer won
    }
  }

  return winner;
}

/**
 * @brief This function will pass arrays of rows, columns and diagonals to the countInEachRowColumnAndDiagonal function to get the game state
 *
 * The game will have 3 states. 1 represents the human won, -1 represents the computer won and 0
 * represents neutrality, the minimax algorithm then uses these states to make it's decisions
 *
 * @param currentBoard This is the board currently being analyzed with the changes made it to from the minimax function
 * @return It returns 1, -1 or 0 depending on whether someone won or the game is neutral
 */
int staticEvaluation(vector<vector<int>> currentBoard)
{
  int numberOfO = 0;
  int numberOfX = 0;
  int winner = 0;

  // If the winner is 0, meaning it's neutral, only then should you check if someone won, otherwise it may override
  // the value of a person that's already won. This is done for all the assignments to this variable
  winner = winner == 0 ? countInEachRowColumnAndDiagonal(currentBoard, numberOfO, numberOfX) : winner;

  // Get all the columns and store them in a vector
  vector<vector<int>> boardColumns;
  for (int i = 0; i < currentBoard.size(); ++i)
  {
    vector<int> temp;
    for (int j = 0; j < currentBoard.size(); ++j)
      temp.push_back(currentBoard[j][i]);
    boardColumns.push_back(temp);
  }
  winner = winner == 0 ? countInEachRowColumnAndDiagonal(boardColumns, numberOfO, numberOfX) : winner;

  // Get all the diagonals and store them in a vector
  vector<vector<int>> boardDiagonals(2);
  for (int i = 0; i < currentBoard.size(); ++i)
  {
    boardDiagonals[0].push_back(currentBoard[i][i]);
    boardDiagonals[1].push_back(currentBoard[i][boardSize - i - 1]);
  }
  winner = winner == 0 ? countInEachRowColumnAndDiagonal(boardDiagonals, numberOfO, numberOfX) : winner;

  return winner;
}

/**
 * @brief This function checks if the game is over given the board being analyzed
 *
 * The conditions under which the game is over are that someone has won or the board is full
 *
 * @param currentBoard The board currently being analyzed
 * @return A boolean value of whether the game is over or not
 */
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

/**
 * @brief The minimax function allows the computer to look at several possibilites of the game and choose the best one
 * @param currentBoard The most up to date board after the user has selected their option
 * @param depth How deep you want the function to recursively call itself
 * @param alpha This is used for alpha-beta pruning just to speed up the algorithm a bit
 * @param beta The same use as beta
 * @param maximizingPlayer If this is true then it is the user's turn since they are the maximizing player otherwise it is the computer
 * @return The first part of the pair is the static evaluation and the second part is the coordinates at which this evaluation was reached
 */
pair<int, pair<int, int>> minimax(vector<vector<int>> currentBoard, int depth, int alpha, int beta, bool maximizingPlayer)
{
  // If either of the conditions are met then you've reached the leaf nodes, so just return who won
  if (depth == 0 || isGameOver(currentBoard))
    return pair<int, pair<int, int>>(staticEvaluation(currentBoard), pair<int, int>(-1, -1));

  // Every done for the maxmizing player is essentially the same for the minimizing one
  if (maximizingPlayer)
  {
    int maxEvaluation = INT32_MIN;
    pair<int, int> maxEvaluationPosition = pair<int, int>(0, 0);
    int evaluation = 0;
    // Loop through all the reamining squares on the board
    for (int i = 0; i < currentBoard.size(); ++i)
    {
      for (int j = 0; j < currentBoard[i].size(); ++j)
      {
        if (currentBoard[i][j] == 0)
        {
          // To check this possibility we assume the person selects this square and then run the function again but this time
          // it's the computer's turn to go through it's possibilities of what it can pick
          currentBoard[i][j] = 1;
          evaluation = minimax(currentBoard, depth - 1, alpha, beta, false).first;

          // If the evaluation, from the leaf node, is greater than the max evaluation so far then it means this position is a good choice
          if (evaluation > maxEvaluation)
          {
            maxEvaluation = evaluation;
            maxEvaluationPosition = pair<int, int>(i, j);
          }

          // Check to see if the evaluation is greater than the alpha, again for alpha beta pruning
          alpha = max(alpha, evaluation);

          // If the beta is less than the alpha then that means the minimizer already has a better option and so they
          // would never pick this path which could lead to the maximizer getting a larger value
          if (beta <= alpha)
            break;

          // Reset the board to what it was before
          currentBoard[i][j] = 0;
        }
      }
    }
    // After all the searching is done return the maximim evaluation found and the position at which it was found
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
          if (beta <= alpha)
            break;
          currentBoard[i][j] = 0;
        }
      }
    }
    return pair<int, pair<int, int>>(minEvaluation, minEvaluationPosition);
  }
}

// Write the data about who one to a file
void saveDataToFile()
{
  ofstream output;

  output.open(FILENAME);
  output << numberOfTimesHumanWon << endl
         << numberOfTimesComputerWon << endl;

  output.close();
}

// Read the data from the file and assign them to the global variables
void openDataFromFile()
{
  ifstream input;

  input.open(FILENAME);
  if (input.fail())
    cout << "Warning: Could not load the scores file." << endl;

  string humanScoreString, computerScoreString;
  getline(input, humanScoreString);
  getline(input, computerScoreString);

  numberOfTimesHumanWon = stoi(humanScoreString);
  numberOfTimesComputerWon = stoi(computerScoreString);
}

// Creates a new game for the user
void newGame()
{
  system("clear");
  boardSize = intInputRange("Please enter the board size you'd like for your new game (3 - 6): ", 3, 6);

  // Reseize the vector so that it has enough memory allocated based on the board size
  board.resize(boardSize);
  for (int i = 0; i < board.size(); ++i)
    board[i].resize(boardSize);

  int row = 0, column = 0;
  drawBoard();
  while (true)
  {
    bool isValid = false;
    // Continue asking the user for a row and column making sure that they don't choose a square that's already been selected
    while (!isValid)
    {
      row = intInputRange("Please select a row (1 - " + to_string(boardSize) + "): ", 1, boardSize);
      column = intInputRange("Please select a column (1 - " + to_string(boardSize) + "): ", 1, boardSize);
      if (board[row - 1][column - 1] != 0)
        cout << "You cannot pick a square that isn't empty, please try again." << endl;
      else
        isValid = true;
    }

    board[row - 1][column - 1] = 1;
    drawBoard();

    if (isGameOver(board))
      break;

    // Have the computer play it's turn with the minimax algorithm
    pair<int, int> position = minimax(board, boardSize == 3 ? 10 : 4, INT32_MIN, INT32_MAX, false).second;
    board[position.first][position.second] = 2;
    drawBoard();

    if (isGameOver(board))
      break;
  }

  // Get the winner using the staticEvalution function
  int winner = staticEvaluation(board);
  if (winner == 0)
  {
    cout << "It's a tie, womp womp. ";
    ++numberOfTimesHumanWon;
    ++numberOfTimesComputerWon;
  }
  else if (winner == 1)
  {
    cout << "Humanity is saved. ";
    ++numberOfTimesHumanWon;
  }
  else
  {
    cout << "The robots are coming. ";
    ++numberOfTimesComputerWon;
  }

  cout << "Press (1) to exit:" << endl;
  int option = -1;
  while (option != 1)
    option = intInputRange("-> ", 1, 1);
  board.clear();
}

/**
 * @brief This function pulls up a menu where you can see how many times the user and computer have won
 */
void viewStats()
{
  system("clear");
  cout << "Stats: " << endl;
  cout << "# of times you won: " << numberOfTimesHumanWon << endl;
  cout << "# of times the computer won: " << numberOfTimesComputerWon << endl;
  cout << endl;

  cout << "Press (1) to exit:" << endl;
  int option = -1;
  while (option != 1)
    option = intInputRange("-> ", 1, 1);
}

int main()
{
  openDataFromFile();
  int option = -1;

  while (true)
  {
    system("clear");

    cout << R"( _____ _      _        _           _____          _        _           _____               
|_   _(_)    | |      | |         |_   _|        | |      | |         |_   _|              
  | |  _  ___| | _____| |_ _   _    | | __ _  ___| | _____| |_ _   _    | | ___   ___  ___ 
  | | | |/ __| |/ / _ \ __| | | |   | |/ _` |/ __| |/ / _ \ __| | | |   | |/ _ \ / _ \/ __|
  | | | | (__|   <  __/ |_| |_| |   | | (_| | (__|   <  __/ |_| |_| |   | | (_) |  __/\__ \
  \_/ |_|\___|_|\_\___|\__|\__, |   \_/\__,_|\___|_|\_\___|\__|\__, |   \_/\___/ \___||___/
                            __/ |                               __/ |                      
                           |___/                               |___/                       )"
         << endl;

    cout << "Welcome! Please select from one of the options below:" << endl;
    cout << "\t(1) Play a new game" << endl;
    cout << "\t(2) View stats" << endl;
    cout << "\t(3) Exit the game" << "\n\n";
    option = intInputRange("\t-> ", 1, 3);

    if (option == 3)
    {
      saveDataToFile();
      cout << "Goodbye! :)\n"
           << endl;
      break;
    }
    else if (option == 2)
      viewStats();
    else
      newGame();
  }

  return 0;
}
