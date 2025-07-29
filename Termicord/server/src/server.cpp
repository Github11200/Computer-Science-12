#include <spdlog/spdlog.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "servers.h"
#include "types.h"
#include "utils/requests.h"
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include <utility>

using namespace std;
using json = nlohmann::json;

int main(int argc, char* argv[]) {
  int PORT = atoi(argv[1]);
  Requests::defaultUrl = "http://localhost:" + to_string(PORT);

  Requests::Request request("/getAllServers", json::parse("{}"));
  Requests::APIResult result = Requests::sendRequest(request);

  vector<pair<string, Server>> servers;
  for (auto& [key, value] : result.data.items()) {
    pair<string, Server> server;
    server.first = key;
    server.second = value.get<Server>(); 
    servers.push_back(server);
  }

  for (auto server : servers)
    Servers::create(server.first, server.second.port); 

  Servers::stop(); // don't forget this!!! 

  return 0;
}
