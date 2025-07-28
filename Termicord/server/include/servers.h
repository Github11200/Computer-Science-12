#ifndef SERVERS_H 
#define SERVERS_H

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

namespace Servers {

extern std::unordered_map<std::string, std::thread*> runningServers;

void serverSocket();
void create(std::string threadName);
void stop();

}

#endif
