#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <string>
#include <nlohmann/json.hpp>

struct User {
  std::vector<std::string> friends;
  std::vector<std::string> servers;
  std::string password;
  std::string name;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(User, friends, servers, password, name);

struct Server {
  std::string owner;
  std::vector<std::string> users;
  int port;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Server, owner, users, port);

#endif
