#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

void burritoBowlDefaultValues(string protein, string rice = "white", string beans = "black", string salsa = "mild")
{
  cout << "Your Burrito Bowl:" << endl;
  cout << "A " << protein << " burrito with " << rice << " rice, " << beans << " beans, and " << salsa << " salsa." << endl;
}

void burritoBowl()
{
  burritoBowlDefaultValues("chicken");
  burritoBowlDefaultValues("steak", "white", "refried", "hot");
  burritoBowlDefaultValues("veggie", "brown");
}

double inputDouble(string prompt)
{
  double input;
  cout << prompt;
  cin >> input;
  return input;
}

double inputDouble(string prompt, double min, double max, string reprompt = "")
{
  double input = inputDouble(prompt);
  while (input < min || input > max)
    input = inputDouble(reprompt);
  return input;
}

int inputInt(string prompt)
{
  int input;
  cout << prompt;
  cin >> input;
  return input;
}

int inputInt(string prompt, int min, int max, string reprompt = "")
{
  int input = inputInt(prompt);
  while (input < min || input > max)
    input = inputInt(reprompt);
  return input;
}

void betterNumberInputs()
{
  double doubleInput = inputDouble("Please enter a double between 0 and 1: ", 0, 1, "That is not between 0 and 1. Try again: ");
  cout << "You entered: " << doubleInput << endl;

  double intInput = inputInt("Please enter an int between 0 and 10: ", 0, 10, "Please try again: ");
  cout << "You entered: " << intInput << endl;
}

string nextAppointmentDay(int currentAppointment, int numberOfDays = 7)
{
  vector<string> days{"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

  return days[((currentAppointment + numberOfDays) % 7) - 1];
}

void appointmentFollowUp()
{
  string type;
  cout << "What type of appointment do you have? ";
  cin >> type;

  int day = 0;
  cout << "Which day is your appointment?" << endl;
  cout << "1: Sunday\n2: Monday\n3: Tuesdayn\n4: Wednesday\n5: Thursday\n6: Friday\n7: Saturday\n";
  cout << "> ";
  cin >> day;

  string nextDay;
  if (type == "Oncologist")
    nextDay = nextAppointmentDay(day, 2);
  else if (type == "Orthodontist")
    nextDay = nextAppointmentDay(day, 10);
  else
    nextDay = nextAppointmentDay(day);
  cout << "Your follow up will be on a " << nextDay << endl;
}

int main()
{
  return 0;
}
