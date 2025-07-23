#include <spdlog/spdlog.h>
#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fstream>
#include <arpa/inet.h>
#include <any>
#include "routing.h"

using namespace std;

int startServerSocket() {
  int socket = socket(AF_INET, SOCK_STREAM, 0);
  if (socket == -1) {
    spdlog::error("Failed to create the socket.");
    return -1;
  }

  spdlog::info("Created the socket.");

  // Prepare the server address
  sockaddr_in serverAddress;
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(PORT);

  // Bind the socket to this address
  if (bind(socket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
    spdlog::error("Failed to bind the server to the server address.");
    return -1;
  }

  spdlog::info("Binded the socket to the server address.");

  // Start listening for incoming connections
  if (listen(socket, 5) == -1) {
    spdlog::error("Failed to listen on the socket.");
    return -1;
  }

  spdlog::info("Server listening on port {}.", PORT);
  return socket;
}

int main(int argc, char* argv[]) {
  int PORT = atoi(argv[1]);

  Routing routing;
  routing.addRoute(Route("/battles", someFunc));

  int serverSocket = startServerSocket();  

  sockaddr_in clientAddress;
  socklen_t clientAddressLen = sizeof(clientAddress);
  int clientSocket = 0;

  while (true) {
    string clientMessage(4096, '\0');

    clientSocket = accept(serverSocket, nullptr, nullptr);

    ssize_t bytesRead = read(clientSocket, clientMessage.data(), clientMessage.size());

    if (bytesRead > 0) {
      clientMessage.resize(bytesRead);
      spdlog::info("Client message: {}", clientMessage);
    } else if (bytesRead == 0) {
      spdlog::info("Client closed connection");
    } else {
      spdlog::error("Read error");
    }

    if (clientSocket == -1) {
      spdlog::error("Failed to accept the connection.");
      return -1; 
    }

    spdlog::info("Accepted the connection from {} : {}.", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));
    
    string httpHeader = "HTTP/1.1 200 OK\r\n\r\n";
    string message = "funny message";

    httpHeader += message; 

    send(clientSocket, httpHeader.c_str(), httpHeader.size(), 0);
    close(clientSocket); 
  }

  close(serverSocket);
  return 0;
}
