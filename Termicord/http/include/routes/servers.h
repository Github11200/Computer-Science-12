#ifndef GET_SERVER_H
#define GET_SERVER_H

#include <iostream>
#include <vector>
#include <string>
#include <uuid/uuid.h>
#include <any>
#include <spdlog/spdlog.h>
#include <optional>
#include <nlohmann/json.hpp>
#include "database/database.h"
#include "types.h"

Result getServer(std::string rawJson);
Result getAllServers(std::string rawJson);
Result addServer(std::string rawJson);
Result addUserToServer(std::string rawJson);

#endif
