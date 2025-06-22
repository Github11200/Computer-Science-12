#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

struct Song
{
  string title, artist;
  int length;
};

void songs()
{
  Song firstSong;
  firstSong.title = "Pink + White";
  firstSong.artist = "Frank Ocean";
  firstSong.length = 185;

  Song secondSong;
  secondSong.title = "Come Again";
  secondSong.artist = "Home Frango";
  secondSong.length = 191;

  cout << firstSong.title << " by " << firstSong.artist << " is " << firstSong.length << " seconds long." << endl;
  cout << secondSong.title << " by " << secondSong.artist << " is " << secondSong.length << " seconds long." << endl;
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

  char option = 'a';
  while (true)
  {
    cout << "Would you like to (a)dd a movie, (l)ist movies, or (e)xit? ";
    cin >> option;
    cin.ignore();
    if (option == 'e')
      break;
    else if (option == 'a')
    {
      Movie newMovie;
      cout << "Please enter the title: ";
      getline(cin, newMovie.title);

      cout << "Please enter an actor(Last, First): ";
      getline(cin, newMovie.actor);

      cout << "Please enter the year: ";
      cin >> newMovie.year;

      cout << "Please enter the rating (1 - 10): ";
      cin >> newMovie.rating;

      movies.push_back(newMovie);
    }
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
