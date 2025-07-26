#ifndef HOME_H 
#define HOME_H 

#include <spdlog/spdlog.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include "windows/auth.h"
#include "utils/input.h"
#include "utils/requests.h"
#include "types.h"

namespace Home {

enum InitOptions {
  LIST_SERVERS = 1,
  ADD_FRIEND = 2,
  EXIT = 3
};

void init();
void listServers();
void selectServer();
void addFriend(); 

}

#endif
