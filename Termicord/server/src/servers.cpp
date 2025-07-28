#include "servers.h"

using namespace std;

namespace Servers {

std::unordered_map<string, thread*> runningServers;

void serverSocket(int PORT) {
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket == -1) {
    spdlog::error("Failed to create the socket.");
    return;
  }

  spdlog::info("Created the socket.");

  // Prepare the server address
  sockaddr_in serverAddress;
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(PORT);

  // Make the port reusable so you don't have to change it every time you run the server
  int yes = 1;
  setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

  // Bind the socket to this address
  if (bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
    spdlog::error("Failed to bind the server to the server address.");
    return;
  }
  
  spdlog::info("Binded the socket to the server address.");
  
  socklen_t addressLength = sizeof(serverAddress);

  if (getsockname(serverSocket, (struct sockaddr*)&serverAddress, &addressLength) == -1) {
    spdlog::error("whoops...");
  } else {
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(serverAddress.sin_addr), ip, sizeof(ip));
    int port = ntohs(serverAddress.sin_port);

    spdlog::info("IP address: {}", ip);
    spdlog::info("Port: {}", port);
  }

  // Start listening for incoming connections
  if (listen(serverSocket, 5) == -1) {
    spdlog::error("Failed to listen on the socket.");
    return;
  }

  sockaddr_in clientAddress;
  socklen_t clientAddressLen = sizeof(clientAddress);
  int clientSocket = accept(serverSocket, (sockaddr*)&clientAddress, &clientAddressLen);
  if (clientSocket == -1) {
    spdlog::error("Failed to accept the connection.");
    return; 
  }

  spdlog::info("Accepted the connection from {} : {}.", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));

  while (true) { 
    char buffer[1024] = { 0 };
    int bytesRecieved = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRecieved <= 0) {
      spdlog::info("The client disconnected.");
      break;
    }
    buffer[bytesRecieved] = '\0';
    spdlog::info("Message from the client: {}", buffer);
  }

  close(serverSocket);
}

void create(string threadName, int PORT) {
  thread* serverSocketThread = new thread(serverSocket, PORT);
  runningServers[threadName] =  serverSocketThread;
}

void stop() {
  for (const auto& server : runningServers) {
    server.second->join();
    delete server.second;
  }
}

}
