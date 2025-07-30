#ifndef DATABASE_H
#define DATABASE_H

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <iostream>
#include <fstream>
#include <optional>
#include <filesystem>

class Database {
private:
  nlohmann::json currentJsonData;
  std::string PATH = "databases/";
  std::string NAME;

public:
  Database(std::string name);
  ~Database();

  void createDatabase();
  bool openDatabase();
  bool databaseExists();
  std::optional<std::string> searchDatabase(std::string key);
  std::string getAllJsonData();
  bool addEntry(std::string key, nlohmann::json jsonData);
  bool updateEntry(std::string key, nlohmann::json newData);
};

#endif
