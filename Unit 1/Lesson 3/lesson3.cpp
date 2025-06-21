#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

void paperSupplier()
{
  int numberOfReams;

  cout << "Please enter the number of reams: ";
  cin >> numberOfReams;

  double costForScott = numberOfReams * 4.09;
  double costForMifflin = 0;
  if (numberOfReams <= 1000)
    costForMifflin = 4.59 * numberOfReams;
  else if (numberOfReams <= 2500)
    costForMifflin = 4.59 * 1000 + 3.99 * (numberOfReams - 1000);
  else
    costForMifflin = 4.59 * 1000 + 3.99 * 1500 + 3.59 * (numberOfReams - 2500);

  cout << "Cost for Dunder Mifflin: " << costForMifflin << endl;
  cout << "Cost for The Michael Scott Paper Company: " << costForScott << endl;

  if (costForMifflin < costForScott)
    cout << "You should stay with Dunder Mifflin" << endl;
  else
    cout << "You should switch to The Michael Scott Paper Company" << endl;
}

void CYOA()
{
  cout << "Your company's prod crashed due to a corrupted repository, and you're using a monolithic repostiry :(" << endl;

  string chosenOption;
  cout << "What are you going to do now?" << endl;
  cout << "\t(\"src\") You're going to enter the src folder, aiming to dbug the core application logic" << endl;
  cout << "\t(\"config\") Go to the config directory, it might be an issue with the system's setup" << endl;
  cout << "\tEnter your choice: ";
  cin >> chosenOption;

  if (chosenOption == "src")
  {
    chosenOption = "";
    cout << endl;
    cout << "You're inside the src folder, now what?" << endl;
    cout << "\t(\"main_loop\") Look at main_loop.py which seems to control the main things in the program" << endl;
    cout << "\t(\"api_handler\") Enter api_handler.js which may be causing a problem with the API requests" << endl;
    cout << "\tEnter your choice: ";
    cin >> chosenOption;

    if (chosenOption == "main_loop")
    {
      chosenOption = "";
      cout << endl;
      cout << "You're inside the algorithm's core, now what?" << endl;
      cout << "\t(\"refactor\") You can refactor a calculate_priority() function to have a better sorting algorithm" << endl;
      cout << "\t(\"trace\") Trace the input data for calculate_priority() in case the data has been corrupted" << endl;
      cout << "\tEnter your choice: ";
      cin >> chosenOption;

      if (chosenOption == "refactor")
        cout << "\nYou refactored calculate_priority() and now the system's performance skyrockets. It turns out, that the algorithm was slowing down the reading and writing of data which sometimes corrupted it" << endl;
      else if (chosenOption == "trace")
        cout << "\nYou found a data type mismatch after tracing, and after you added in a data validation layer the system runs perfectly" << endl;
    }
    else if (chosenOption == "api_handler")
    {
      chosenOption = "";
      cout << endl;
      cout << "You're inside the api_handler.js file, now what?" << endl;
      cout << "\t(\"optimize\") You can optimize the request_processor() function so the api processes requests faster" << endl;
      cout << "\t(\"check\") You can check the auth_token_generator() methdo to see if the authentication is failing" << endl;
      cout << "\tEnter your choice: ";
      cin >> chosenOption;

      if (chosenOption == "optimize")
        cout << "\nYou've implemented async calls and caching so the API can handle a bunch of requests without it crashing, you have happy users now :)" << endl;
      else if (chosenOption == "check")
        cout << "\nYou found a vulnerability that led to expired tokens, and after patching this you're app won't get DDoSed" << endl;
    }
  }
  else if (chosenOption == "config")
  {
    chosenOption = "";
    cout << endl;
    cout << "You're inside the config directory, now what?" << endl;
    cout << "\t(\"network_settings\") Look at network_settings.json to see if the syntax is messed up" << endl;
    cout << "\t(\"hidden_defaults\") Look at hidden_defaults.yaml where you have no idea on what it contains" << endl;
    cout << "\tEnter your choice: ";
    cin >> chosenOption;

    if (chosenOption == "network_settings")
    {
      chosenOption = "";
      cout << endl;
      cout << "You're inside the network_settings.json file, now what?" << endl;
      cout << "\t(\"adjust\") You can adjust the port number so it matches the server's requirements because it seems to be wrong" << endl;
      cout << "\t(\"automate\") You can automate the port negotiation script so there aren't mismatches in the future" << endl;
      cout << "\tEnter your choice: ";
      cin >> chosenOption;

      if (chosenOption == "adjust")
        cout << "\nYou changed the port number and now the system is able to communicate with other services smoothly, at least for now" << endl;
      else if (chosenOption == "automate")
        cout << "\nYou implemented a port negotiation script and nwo you can change network environments without your system blowing up" << endl;
    }
    else if (chosenOption == "hidden_defaults")
    {
      chosenOption = "";
      cout << endl;
      cout << "You're inside the hidden_defaults.yaml file, now what?" << endl;
      cout << "\t(\"debug_mode_active\") Turn the debug_mode_active to false so there isn't verbose logging" << endl;
      cout << "\t(\"delete\") Delete the hidden_defaults.yaml file as it may be legacy code" << endl;
      cout << "\tEnter your choice: ";
      cin >> chosenOption;

      if (chosenOption == "debug_mode_active")
        cout << "\nYou don't have a river of logs and now the system runs efficiently and quickly" << endl;
      else if (chosenOption == "delete")
        cout << "\nTurns out the file wasn't legacy code and it was just badly named, your whole company falls into chapter 11 bankruptcy, whoops" << endl;
    }
  }
}

int main()
{
  return 0;
}
