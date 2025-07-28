#ifndef AUTH_H
#define AUTH_H

#include <spdlog/spdlog.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include "utils/input.h"
#include "utils/requests.h"
#include "types.h"

namespace Auth {

extern std::string username;
extern User currentUser;

enum AuthType {
  LOGIN = 1,
  SIGN_UP = 2
};

enum NextStep {
  RETRY = 1,
  EXIT = 2
};

void init();
void login();
void signUp();

}

#endif
