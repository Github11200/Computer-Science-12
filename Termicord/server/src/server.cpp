#include <spdlog/spdlog.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "servers.h"
#include "utils/requests.h"
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

using namespace std;
using json = nlohmann::json;

struct Server {
  std::string owner;
  std::vector<std::string> users;
  std::string serverName;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Server, owner, users);

int main(int argc, char* argv[]) {
  int PORT = atoi(argv[1]);
  Requests::defaultUrl = "http://localhost:" + to_string(PORT);

  Requests::Request request("/getAllServers", json::parse("{}"));
  Requests::APIResult result = Requests::sendRequest(request);

  vector<Server> servers;
  for (auto& [key, value] : result.data.items()) {
    Server server = value.get<Server>();
    server.serverName = key;
    servers.push_back(server);
  }

  for (Server server : servers) {
    Servers::create(server.serverName);
  }
  Servers::stop(); // don't forget this!!! 

  return 0;
}
