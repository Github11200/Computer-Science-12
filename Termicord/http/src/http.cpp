#include <spdlog/spdlog.h>
#include <uuid>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

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
#include "database/database.h"

using namespace std;
using uuids = boost::uuids;

int startServerSocket(int PORT) {
  uuids::random_generator generator;
  uuids::uuid uuid = generator();
  cout << uuid << endl;

  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket == -1) {
    spdlog::error("Failed to create the socket.");
    return -1;
  }

  spdlog::info("Created the socket on port {}", PORT);

  // Prepare the server address
  sockaddr_in serverAddress;
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(PORT);

  // Bind the socket to this address
  if (bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
    spdlog::error("Failed to bind the server to the server address.");
    return -1;
  }

  spdlog::info("Binded the socket to the server address.");

  // Start listening for incoming connections
  if (listen(serverSocket, 5) == -1) {
    spdlog::error("Failed to listen on the socket.");
    return -1;
  }

  spdlog::info("Server listening on port {}.", PORT);
  return serverSocket;
}

string readFromSocket(int clientSocket) { 
  string clientMessage(4096, '\0');
  ssize_t bytesRead = read(clientSocket, clientMessage.data(), clientMessage.size());

  if (bytesRead > 0) 
    clientMessage.resize(bytesRead);
  else if (bytesRead == 0) 
    spdlog::info("Client closed connection");
  else 
    spdlog::error("Read error");

  return clientMessage;
} 

int main(int argc, char* argv[]) {
  int PORT = atoi(argv[1]);

  Routing routing;

  int serverSocket = startServerSocket(PORT);  

  sockaddr_in clientAddress;
  socklen_t clientAddressLen = sizeof(clientAddress);
  int clientSocket = 0;

  while (true) {
    clientSocket = accept(serverSocket, nullptr, nullptr);

    if (clientSocket == -1) {
      spdlog::error("Failed to accept the connection.");
      return -1; 
    }

    string clientMessage = readFromSocket(clientSocket);
    string header = clientMessage.substr(0, clientMessage.find('\n'));
    string method = clientMessage.substr(0, clientMessage.find(' '));
    spdlog::info("Method: {}", method);
    spdlog::info("Route: {}", routing.getRouteNameFromHeader(header));

    spdlog::info("Accepted the connection from {} : {}.", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));
    
    string httpHeader = "HTTP/1.1 200 OK\r\n\r\n";
    string message = "funny as message";

    httpHeader += message; 

    send(clientSocket, httpHeader.c_str(), httpHeader.size(), 0);
    close(clientSocket); 
  }

  close(serverSocket);
  return 0;
}
