#include <spdlog/spdlog.h>
#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fstream>
#include <arpa/inet.h>

using namespace std;

int main(int argc, char* argv[]) {
  int PORT = atoi(argv[1]);

  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket == -1) {
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

  sockaddr_in clientAddress;
  socklen_t clientAddressLen = sizeof(clientAddress);
  int clientSocket = accept(serverSocket, nullptr, nullptr);
  if (clientSocket == -1) {
    spdlog::error("Failed to accept the connection.");
    return -1; 
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

  return 0;
}
