#include "routes/users.h"

using namespace std;
using json = nlohmann::json;

const string NAME = "users";

Result getUser(string rawJson) {
  Database database(NAME);
  json httpRequest = json::parse(rawJson);

  optional<string> searchResult = database.searchDatabase(httpRequest["username"].get<string>());  
  if (searchResult) 
    return Result(200, *searchResult);

  spdlog::error("Could not find the requested user in the database");
  return Result(500, "{ \"message\": \"Error, could not find the user in the database.\" }"); 
}

Result getAllUsers(string rawJson) {
  Database database(NAME);
  return Result(200, database.getAllJsonData());
}

Result addUser(string rawJson) {
  Database database(NAME);
  json httpRequest = json::parse(rawJson);

  string key = httpRequest["username"].get<string>();

  // Remove the username key and then pass the rest of the json object
  httpRequest.erase("username");
  if (database.addEntry(key, httpRequest))
    return Result(200, "{ \"message\": \"Added the user to the database\" }");
  return Result(500, "{ \"message\": \"The user already exists\" }");
}
