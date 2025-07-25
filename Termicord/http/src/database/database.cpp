#include "database/database.h"

using namespace std;
using json = nlohmann::json;

void Database::createDatabase(string name) {
  fstream database(this->PATH + name + ".json", ios::out | ios::trunc);

  if (!database.is_open()) {
    spdlog::error("Could not create a new database");
    return;
  }

  database << "{}";
  
  this->currentJsonData = json::parse("{}"); 
  database.close();

  spdlog::info("Successfully created the database \"{}\"", name); 
}

void Database::openDatabase(string name) {
  fstream database(this->PATH + name + ".json");

  if (!database.is_open()) {
    spdlog::error("Could not open the database");
    return;
  }

  database >> this->currentJsonData;
  spdlog::info("Successfully opened and loaded the database");
}

bool Database::databaseExists(string name) {
  ifstream file(this->PATH + name + ".json");
  if (file) return true;
  else return false;
}

optional<string> Database::searchDatabase(string key) {
  if (this->currentJsonData.contains(key))
    return this->currentJsonData[key].dump();
  return nullopt;
}

string Database::getAllJsonData() {
  return this->currentJsonData.dump();
}

void Database::closeDatabase() {
  this->currentJsonData = json::parse("");
  spdlog::info("Successfully closed the database");
}
