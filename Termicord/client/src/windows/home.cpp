#include "windows/home.h"
#include "utils/requests.h"
#include "windows/auth.h"

using namespace std;
using json = nlohmann::json;

namespace Home {

void init() {
  while (true) {
    system("clear");
    cout << "Welcome " << Auth::currentUser.username << "!\n\n";

    InitOptions initOption;
    Input::getOption<InitOptions>(
        "What would you like to do?",
        vector<string>({"List all servers", "Add a friend", "Exit"}),
        initOption);
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
    Input::getBoundedNumericInput<int>(
        "Which server would you like to join and/or modify (1 - " +
            to_string(servers.size()) + "). Input 0 to exit: ",
        serverIndex, 0, servers.size());
    if (serverIndex == 0)
      return;
    selectedServer(servers[serverIndex - 1]);
  }
}

void selectedServer(string serverName) {
  system("clear");

  json j = {{"server_name", serverName}};
  Requests::Request request("/getServer", j);
  Requests::APIResult result = Requests::sendRequest(request);

  if (result.code == Requests::ResponseCode::SUCCESS) {
    while (true) {
      Server server = result.data.get<Server>();
      ServerOperation serverOperation;
      Input::getOption<ServerOperation>(
          "What would you like to do with the following server: " + serverName,
          vector<string>({"Join server", "Add user", "Cancel"}),
          serverOperation);

      if (serverOperation == ServerOperation::JOIN_SERVER) {
        Chat::join(server.port);
      } else if (serverOperation == ServerOperation::ADD_USER) {
        system("clear");
        if (server.owner != Auth::currentUser.username) {
          cout << "You are not the owner of this server and cannot add users. "
                  "Please press enter to continue"
               << endl;
          cin.get();
          continue;
        }
        string username = "";
        Input::getStringInput(
            "What is the username of the person you'd like to add? ", username);

        json addUserJson = {{"server_name", serverName},
                            {"username", username}};

        cpr::Response addUserToServerResponse =
            cpr::Post(cpr::Url{"http://localhost:8000/addUserToServer"},
                      cpr::Header{{"Content-Type", "application/json"}},
                      cpr::Body{addUserJson.dump()});
        cpr::Response addServerToUserResponse =
            cpr::Post(cpr::Url{"http://localhost:8000/addServerToUser"},
                      cpr::Header{{"Content-Type", "application/json"}},
                      cpr::Body{addUserJson.dump()});

        system("clear");
        if (addUserToServerResponse.status_code ==
                Requests::ResponseCode::SUCCESS &&
            addServerToUserResponse.status_code ==
                Requests::ResponseCode::SUCCESS)
          cout << "The user was added successfully! Please press enter to "
                  "continue";
        else
          cout << "There was an error adding the user. Please press enter to "
                  "continue";

        cin.ignore();
        cin.get();
      } else if (serverOperation == ServerOperation::CANCEL) {
        return;
      }
    }
  } else if (result.code == Requests::ResponseCode::INTERNAL_SERVER_ERROR) {
    cout << "Could fetch the server :(" << endl;
  }
}

void addFriend() {
  system("clear");
  string friendUsername = "";
  Input::getStringInput("What is the username of the friend? ", friendUsername);

  json j = {{"username", Auth::currentUser.username},
            {"friend", friendUsername}};
  Requests::Request request("/addFriend", j);
  Requests::APIResult result = Requests::sendRequest(request);

  system("clear");
  if (result.code == Requests::ResponseCode::SUCCESS)
    cout << "Your new friend is ready to chat with :). Please press enter to "
            "continue.";
  else if (result.code == Requests::ResponseCode::INTERNAL_SERVER_ERROR)
    cout << "There was an error adding this friend. It's okay though, you can "
            "still talk in real life :). Please press enter to continue.";
  cin.ignore();
  cin.get();
}

} // namespace Home
