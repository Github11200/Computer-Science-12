#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

void haiku()
{
  string line1 = "Keys tap in silence";
  string line2 = "Logic flows through tangled lines";
  string line3 = "Dreams become real code";

  cout << line1 << endl
       << line2 << endl
       << line3 << endl;
}

void favorites()
{
  string favoriteSubject, favoriteArtist, favoriteActivity;

  cout << "Please enter your favorite school subject: ";
  getline(cin, favoriteSubject);

  cout << "Please enter your favorite musical artist or band: ";
  getline(cin, favoriteArtist);

  cout << "Please enter your favorite after-school activity: ";
  getline(cin, favoriteActivity);

  cout << "Favorite subject: " << favoriteSubject << endl;
  cout << "Favorite artist or band: " << favoriteArtist << endl;
  cout << "Favorite after-school activity: " << favoriteActivity << endl;
}

void putTheCodeInOrder()
{
  //   #include <iostream>

  //   using namespace std;

  //   int main()
  //   {
  //     cout << "I like to ";
  //     cout << "fetch tennis balls!" << endl;
  //     return 0;
  //   }
}

int main()
{
  favorites();

  return 0;
}
