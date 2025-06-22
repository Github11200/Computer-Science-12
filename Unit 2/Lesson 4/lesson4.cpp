#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

void sumFromAFile()
{
  ifstream input;
  string fileName;

  cout << "Please enter a file name: ";
  cin >> fileName;

  input.open(fileName);
  if (input.fail())
  {
    cout << "Could not open the file." << endl;
    return;
  }

  double sum = 0;
  string currentNumber;
  while (true)
  {
    getline(input, currentNumber);
    if (input.fail())
      break;
    sum += stod(currentNumber);
  }

  cout << "The sum is " << sum << endl;

  input.close();
}

struct Movie
{
  string title, actor;
  int year;
  double rating;
};

void movies()
{
  vector<Movie> movies;
  ifstream input;
  input.open("movies.txt");

  if (input.fail())
  {
    cout << "Could not open the file." << endl;
    return;
  }

  string line;
  while (true)
  {
    getline(input, line);
    if (input.fail())
      break;

    stringstream lineStream(line);
    vector<string> values;
    string token;
    while (getline(lineStream, token, ';'))
      values.push_back(token);

    Movie newMovie;
    newMovie.title = values[0];
    newMovie.year = stoi(values[1]);
    newMovie.actor = values[2];
    newMovie.rating = stod(values[3]);
    movies.push_back(newMovie);
  }

  input.close();

  char option = 'a';
  while (true)
  {
    cout << "Would you like to (l)ist movies or (e)xit? ";
    cin >> option;
    cin.ignore();
    if (option == 'e')
      break;
    else if (option == 'l')
    {
      cout << endl;
      for (Movie movie : movies)
      {
        cout << "Title: " << movie.title << endl;
        cout << "Year: " << movie.year << endl;
        cout << "Actor: " << movie.actor << endl;
        cout << "Rating: " << movie.rating << endl;
      }
    }
  }
}

int main()
{
  return 0;
}
