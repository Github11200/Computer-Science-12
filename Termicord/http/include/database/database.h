#ifndef DATABASE_H
#define DATABASE_H

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <iostream>
#include <fstream>
#include <optional>

class Database {
private:
  nlohmann::json currentJsonData;
  std::string PATH = "databases/";

public:
  Database() = default;

  void createDatabase(std::string name);
  void openDatabase(std::string name);
  bool databaseExists(std::string name);
  std::optional<std::string> searchDatabase(std::string key);
  std::string getAllJsonData();
  void closeDatabase();
};

#endif
