#include "database/database.h"

using namespace std;
using json = nlohmann::json;

Database::Database(std::string databasesPath) {
  this->databasesPath = databasesPath;
}

void Database::createDatabase(string name) {
  ifstream database(databasesPath + name);

  if (database.fail()) {
    spdlog::error("Could not create a new database");
    return;
  }

  database << "({})";
  
  this->currentJsonData = json::parse("({})");
  this->currentDatabase = database;

  spdlog::info("Successfully created a new database");
}

void Database::openDatabase(string name) {
  ifstream database(databasesPath + name);

  if (database.fail()) {
    spdlog::error("Could not open the database");
    return;
  }

  spdlog::info("Successfully opened and loaded the database");
}

void Database::searchDatabase() {}

void Database::closeDatabase() {
  this->currentDatabase.close();
  this->currentJsonData = json::parse("");
  spdlog::info("Successfully closed the database");
}
