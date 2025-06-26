#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

struct Car
{
  string make;
  string model;
  string color;
  int year;
};

int main()
{
  int option;
  map<string, Car> cars;

  while (true)
  {
    cout << "Please select an option:" << endl;
    cout << "1. Register Car" << endl;
    cout << "2. Search for a car" << endl;
    cout << "3. Exit" << endl;
    cout << ">> ";
    cin >> option;

    if (option == 3)
      break;
    else if (option == 1)
    {
      string licensePlateNumber;
      Car newCar;

      cout << "Enter the new license plate number: ";
      cin >> licensePlateNumber;
      cin.ignore();

      if (cars.find(licensePlateNumber) != cars.end())
      {
        cout << "A car with that license plate is already registered." << endl;
        continue;
      }

      cout << "Enter the make of your car: ";
      getline(cin, newCar.make);

      cout << "Enter the model of your car: ";
      getline(cin, newCar.model);

      cout << "Enter the color of the car: ";
      getline(cin, newCar.color);

      cout << "Enter the year of your car (YYYY): ";
      cin >> newCar.year;

      cars[licensePlateNumber] = newCar;
    }
    else
    {
      string licensePlateNumber;

      cout << "Enter the license plate number to search: ";
      cin >> licensePlateNumber;

      if (cars.find(licensePlateNumber) != cars.end())
      {
        Car car = cars[licensePlateNumber];
        cout << "Year: " << car.year << endl;
        cout << "Make " << car.make << endl;
        cout << "Model " << car.model << endl;
        cout << "Color: " << car.color << endl;
      }
      else
        cout << "No car with that plate found." << endl;
    }
  }

  return 0;
}
