#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <iostream>
#include <fstream>

class Database {
private:
  std::ifstream currentDatabase;
  nlohmann::json currentJsonData;
  std::string databasesPath;

public:
  Database(std::string databasesPath);

  void createDatabase(std::string name);
  void openDatabase(std::string name);
  void searchDatabase();
  void closeDatabase();
};
