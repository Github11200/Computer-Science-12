#ifndef PROXY_H
#define PROXY_H

#include <spdlog/spdlog.h>
#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fstream>
#include <arpa/inet.h>
#include <thread>
#include <unordered_map>
#include <nlohmann/json.hpp>

namespace Proxy {

extern std::thread* proxyThread;

void proxyThreadCallback();
void create();
void stop();

}

#endif
