#include <spdlog/spdlog.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <nlohmann/json.hpp>
#include <string>
#include "utils/input.h"
#include "utils/requests.h"
#include "windows/auth.h"
#include "windows/home.h"

using namespace std;
using json = nlohmann::json;

int main(int argc, char* argv[]) {
  int PORT = atoi(argv[1]);
  Requests::defaultUrl = "http://localhost:" + to_string(PORT);

  Auth::init();


  return 0;
}

// int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
//
// sockaddr_in serverAddress;
// serverAddress.sin_family = AF_INET;
// serverAddress.sin_port = htons(PORT);
// serverAddress.sin_addr.s_addr = INADDR_ANY;
// inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);
//
// connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
// string stringMessage = "";
//
// while (getline(cin, stringMessage) && stringMessage != "exit") { 
//   ssize_t sent = send(clientSocket, stringMessage.data(), stringMessage.size(), 0);
//   if (sent < 0) {
//     spdlog::error("Could not send.");
//     break;
//   }
// } 
//
// close(clientSocket);
