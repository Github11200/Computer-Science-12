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
#include <mutex>
#include <set>
#include "types.h"

namespace Servers {

extern std::unordered_map<std::string, std::thread*> runningServers;
extern std::set<int> connectedClientSockets; 
extern std::mutex receivingThreadMutex;

void broadcastMessage(std::string message, int excludedClient); 
void receivingThreadCallback(int clientSocket);
void serverSocket(int PORT);
void create(std::string threadName, int PORT);
void stop();

}

#endif
