#ifndef MENU_H
#define MENU_H

#include <spdlog/spdlog.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include "utils/input.h"
#include "utils/requests.h"
#include "types.h"

namespace Menu {

void init();
void listServers();

}

#endif
