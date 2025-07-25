#include "routes/getUser.h"

using namespace std;
using json = nlohmann::json;

Result getUser(string rawJson) {
  Database database;
  json httpRequest = json::parse(rawJson);
  
  if (!database.databaseExists("users")) {
    database.createDatabase("users");
    spdlog::warn("The users database was not found so a new database was created");
    return Result(500, "{ \"message\": \"Error, the users database did not exist so it was just created\" }");
  }

  database.openDatabase("users");

  optional<string> searchResult = database.searchDatabase(httpRequest["user_id"].get<string>()); 
  if (searchResult) 
    return Result(200, *searchResult);

  spdlog::error("Could not find the requested user in the database");
  return Result(500, "{ \"message\": \"Error, could not find the user in the database.\" }"); 
}

Result getAllUsers(string rawJson) {
  Database database;

  if (!database.databaseExists("users")) {
    database.createDatabase("users");
    spdlog::warn("The users database was not found so a new database was created");
    return Result(500, "{ \"message\": \"Error, the users database did not exist so it was just created\" }");
  }

  database.openDatabase("users");
  spdlog::info("users data: {}", database.getAllJsonData());
  return Result(200, database.getAllJsonData());
}
