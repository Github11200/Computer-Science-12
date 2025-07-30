#ifndef CHAT_H
#define CHAT_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include "windows/auth.h"
#include "utils/input.h"
#include "utils/requests.h"
#include "types.h"

namespace Chat {

extern std::vector<std::string> messages;
extern std::mutex mtx;

void displayMessages();
void receive(int socket);
void join(int PORT);

}

#endif
