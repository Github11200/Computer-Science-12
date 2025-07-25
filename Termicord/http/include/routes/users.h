#ifndef GET_USER_H
#define GET_USER_H

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
#include "utils.h"

Result getUser(std::string rawJson);
Result getAllUsers(std::string rawJson);
Result addUser(std::string rawJson);

#endif
