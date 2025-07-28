#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

struct Server {
  std::string owner;
  std::vector<std::string> users;
  int port;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Server, owner, users, port);

#endif
