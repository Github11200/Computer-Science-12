#include "windows/home.h"

using namespace std;
using json = nlohmann::json;

namespace Home {

void init() {
  cout << "Welcome " << Auth::username << "!\n\n";

  int initOption = 0;
  Input::getOption<InitOptions>("What would you like to do?", vector<string>({"List all servers", "Add a friend", "Exit"}), initOption);
  if (initOption == InitOptions::LIST_SERVERS)
    listServers();
  else if (initOption == InitOptions::ADD_FRIEND)
    addFriend();
  else if (initOption == InitOptions::EXIT) {
    cout << "Goodbye!" << endl;
    return;
  }
}

void listServers() {
  system("clear");
  Requests::Request request("/getAllServers", json::parse("{}"));
  Requests::APIResult result = Requests::sendRequest(request);

  if (result.code == Requests::ResponseCode::SUCCESS) {
    // Loop through all the server ids and print them out 
  } else if (result.code == Requests::ResponseCode::INTERNAL_SERVER_ERROR) { 

  } 
}

void selectServer() {

}

void addFriend() {

}

}
