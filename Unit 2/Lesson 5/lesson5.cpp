#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>
#include <ctime>

using namespace std;

void nextBirthday()
{
  string ageInput;
  int age;
  bool isValid = false;

  while (!isValid)
  {
    try
    {
      cout << "Please enter your age: ";
      cin >> ageInput;
      age = stoi(ageInput);

      if (age < 2)
        throw logic_error("Age invalid. Too young.");
      if (age > 110)
        throw logic_error("Age invalid. Too old.");

      isValid = true;
    }
    catch (invalid_argument)
    {
      cout << "Please enter a valid number." << endl;
    }
    catch (exception const &e)
    {
      cout << e.what() << endl;
    }
  }

  cout << "On your next birthday, you will be " << (age + 1) << " years old." << endl;
}

struct Movie
{
  string title, actor;
  int year;
  double rating;
};

int getCurrentYear()
{
  auto t = time(nullptr);
  auto localTimeInfo = localtime(&t);
  return 1900 + localTimeInfo->tm_year;
}

void readMoviesFromFile(vector<Movie> &movies)
{
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
}

void listMovies(vector<Movie> &movies)
{
  cout << endl;
  int count = 0;
  for (Movie movie : movies)
  {
    cout << "Title: " << movie.title << endl;
    cout << "Year: " << movie.year << endl;
    cout << "Actor: " << movie.actor << endl;
    cout << "Rating: " << movie.rating << endl;
    ++count;
  }
  cout << endl;
  cout << "Total Count: " << count << endl;
}

void searchMovies(vector<Movie> &movies)
{
  string searchOption;
  int searchOptionNumber;
  bool isValid = false;

  cout << "Search menu:" << endl;
  cout << "1. Search by Title" << endl;
  cout << "2. Search by Year" << endl;
  cout << "3. Search by Actor" << endl;
  cout << "4. Search by Rating" << endl;

  while (!isValid)
  {
    cout << "Enter option: ";
    cin >> searchOption;
    try
    {
      searchOptionNumber = stoi(searchOption);
      if (searchOptionNumber < 1 || searchOptionNumber > 4)
        throw logic_error("Please enter a number between 1 and 4.");

      isValid = true;
    }
    catch (invalid_argument)
    {
      cout << "Not a valid number. Please try again." << endl;
    }
    catch (exception const &e)
    {
      cout << e.what() << endl;
    }
  }

  string message;
  cin.ignore();
  if (searchOptionNumber == 1)
  {
    string title;
    cout << "Please enter a title to search for: ";
    getline(cin, title);
    vector<Movie> searchedMovies;
    for (Movie movie : movies)
      if (movie.title.find(title) != string::npos)
        searchedMovies.push_back(movie);
    listMovies(searchedMovies);
  }
  else if (searchOptionNumber == 2)
  {
    string year1String, year2String;
    int year1, year2;
    bool isYearInvalid = true;

    while (isYearInvalid)
    {
      try
      {
        cout << "Please enter the starting year to search for: ";
        cin >> year1String;
        year1 = stoi(year1String);

        if (year1 > getCurrentYear())
          throw logic_error("You cannot input a year into the future. Try again.");
        isYearInvalid = false;
      }
      catch (invalid_argument)
      {
        cout << "Not a valid number. Please try again." << endl;
      }
      catch (exception const &e)
      {
        cout << e.what() << endl;
      }
    }

    isYearInvalid = true;
    while (isYearInvalid)
    {
      try
      {
        cout << "Please enter the ending year to search for: ";
        cin >> year2String;
        year2 = stoi(year2String);

        if (year2 > getCurrentYear())
          throw logic_error("You cannot input a year into the future. Try again.");
        else if (year2 < year1)
          throw logic_error("You cannot input a year smaller than the start year. Try again.");

        isYearInvalid = false;
      }
      catch (invalid_argument)
      {
        cout << "Not a valid number. Please try again." << endl;
      }
      catch (exception const &e)
      {
        cout << e.what() << endl;
      }
    }

    vector<Movie> searchedMovies;
    for (Movie movie : movies)
      if (movie.year >= year1 && movie.year <= year2)
        searchedMovies.push_back(movie);
    listMovies(searchedMovies);
  }
  else if (searchOptionNumber == 3)
  {
    string actor;
    cout << "Please enter an actor to search for: " << endl;
    getline(cin, actor);
    vector<Movie> searchedMovies;
    for (Movie movie : movies)
      if (movie.actor.find(actor) != string::npos)
        searchedMovies.push_back(movie);
    listMovies(searchedMovies);
  }
  else if (searchOptionNumber == 4)
  {
    string ratingString;
    int rating;
    bool isRatingInvalid = true;

    while (isRatingInvalid)
    {
      try
      {
        cout << "Please enter a rating to search for: ";
        cin >> ratingString;
        rating = stoi(ratingString);

        if (rating < 1 || rating > 10)
          throw logic_error("The rating must be between 1 - 10. Please try again.");

        isRatingInvalid = false;
      }
      catch (invalid_argument)
      {
        cout << "Not a valid number. Please try again." << endl;
      }
      catch (exception const &e)
      {
        cout << e.what() << endl;
      }
    }

    vector<Movie> searchedMovies;
    for (Movie movie : movies)
      if (movie.rating == rating)
        searchedMovies.push_back(movie);
    listMovies(searchedMovies);
  }
}

void movies()
{
  vector<Movie> movies;
  readMoviesFromFile(movies);

  char option = 'a';
  while (true)
  {
    cout << "Would you like to (s)earch, (l)ist movies or (e)xit? ";
    cin >> option;
    cin.ignore();
    if (option == 'e')
      break;
    else if (option == 'l')
      listMovies(movies);
    else if (option == 's')
      searchMovies(movies);
  }
}

int main()
{
  movies();
  return 0;
}
