#include "util.h"
#include <vector>

struct Patient
{
  string name;
  double temperature;
};

int main()
{
  vector<Patient> patients;

  string name = "";
  double temperature = 0;
  while (true)
  {
    name = readLine("Please enter the patient's name ('exit' when done): ");
    if (name == "exit")
      break;
    temperature = readDouble(95, 106, "Please enter their temperature: ", "Temperature should be between 95 and 106: ");

    Patient patient;
    patient.name = toUpperCase(name);
    patient.temperature = temperature;

    patients.push_back(patient);
  }

  cout << "The following patients may attend:" << endl;
  for (Patient patient : patients)
    if (patient.temperature < 100)
      cout << patient.name << endl;

  return 0;
}