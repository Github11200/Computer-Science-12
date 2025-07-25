#include "routes/servers.h"

using namespace std;
using json = nlohmann::json;

const string NAME = "servers";

Result getServer(string rawJson) {
  Database database(NAME);
  json httpRequest = json::parse(rawJson);

  optional<string> searchResult = database.searchDatabase(httpRequest["server_name"].get<string>());
  if (searchResult)
    return Result(200, *searchResult);

  spdlog::error("Could not find the requested server in the database");
  return Result(500, "{ \"message\": \"Error, could not find the server in the database.\" }");
}

Result getAllServers(string rawJson) {
  Database database(NAME);
  return Result(200, database.getAllJsonData());
}

Result addServer(string rawJson) {
  Database database(NAME);
  json httpRequest = json::parse(rawJson);

  string key = httpRequest["server_name"].get<string>();

  httpRequest.erase("server_name");
  if (database.addEntry(key, httpRequest))
    return Result(200, "{ \"message\": \"Added the server to the database\" }");
  return Result(500, "{ \"message\": \"The server already exists\" }");  
} 
