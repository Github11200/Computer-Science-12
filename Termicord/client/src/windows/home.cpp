#include "windows/home.h"

using namespace std;
using json = nlohmann::json;

namespace Home {

void init() {
  while (true) {
    system("clear");
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
}

void listServers() {
  while (true) {
    system("clear");

    vector<string> servers;
    for (int i = 0; i < Auth::currentUser.servers.size(); ++i) {
      string currentServer = Auth::currentUser.servers[i];
      cout << "(" << i + 1 << ") " << currentServer << endl;
      servers.push_back(currentServer);
    }

    int serverIndex = 0;
    Input::getBoundedNumericInput<int>("Which server would you like to join and/or modify (1 - " + to_string(servers.size()) + "). Input 0 to exit: ", serverIndex, 0, servers.size());
    if (serverIndex == 0)
      return;
    selectedServer(servers[serverIndex - 1]);
  }
}

void selectedServer(string serverName) {
  system("clear");
 
  json j = json::parse("{ \"server_name\": \"" + serverName + "\" }");
  Requests::Request request("/getServer", j);
  Requests::APIResult result = Requests::sendRequest(request);

  if (result.code == Requests::ResponseCode::SUCCESS) {
    while (true) {
      Server server = result.data.get<Server>();
      int serverOperation = 0;
      Input::getOption<ServerOperation>("What would you like to do with the following server: " + serverName, vector<string>({"Join server", "Add user", "Cancel"}), serverOperation);

      if (serverOperation == ServerOperation::JOIN_SERVER) {
        // Join server code here
      } else if (serverOperation == ServerOperation::ADD_USER) {
        system("clear");
        if (server.owner != Auth::username) {
          cout << "You are not the owner of this server and cannot add users. Please press enter to continue" << endl;
          cin.get();
          continue;
        }
        string username = "";
        Input::getStringInput("What is the username of the person you'd like to add?", username);

        // TODO: add the user somehow :)
      } else if (serverOperation == ServerOperation::CANCEL) {
        return;
      }
    }
  } else if (result.code == Requests::ResponseCode::INTERNAL_SERVER_ERROR) {
    cout << "Could fetch the server :(" << endl;
  }
}

void addFriend() {

}

}
