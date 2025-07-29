#ifndef AUTH_H
#define AUTH_H

#include <spdlog/spdlog.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <cpr/cpr.h>
#include "utils/input.h"
#include "utils/requests.h"
#include "types.h"

namespace Auth {

extern User currentUser;

enum class AuthType {
  LOGIN = 1,
  SIGN_UP = 2
};

enum class NextStep {
  RETRY = 1,
  EXIT = 2
};

void init();
void login();
void signUp();

}

#endif
