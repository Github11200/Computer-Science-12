#include "servers.h"

using namespace std;

namespace Servers {

unordered_map<string, thread*> runningServers;
mutex receivingThreadMutex;
set<int> connectedClientSockets;
vector<string> messages;

void broadcastMessage(string message, int excludedClient) {
  messages.push_back(message);
  for (int client : connectedClientSockets) {
    if (client != excludedClient) {
      ssize_t sent = send(client, message.data(), message.size(), 0);
      if (sent < 0)
        spdlog::error("Could not send.");  
    }
  }
}

void receivingThreadCallback(int clientSocket) {
  char buffer[1024] = { 0 };
  bool firstLoop = true;
  string username = "";
  while (true) {
    int bytesRecieved = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRecieved <= 0) {
      spdlog::info("The client disconnected.");
      connectedClientSockets.erase(clientSocket);
      break;
    }
    buffer[bytesRecieved] = '\0';

    // The very first message the client sends will always be the username
    // Also send the chat history so far to the user
    if (firstLoop) {
      username = string(buffer);
      firstLoop = false;
      for (const string& message : messages) {
        string messageUsername = "";
        int i = 1;
        for (; message[i] != ']'; ++i)
          messageUsername += message[i];
        ssize_t sent;
        if (messageUsername == username) {
          string newMessage = "[You] " + message.substr(i, 2);
          sent = send(clientSocket, newMessage.data(), newMessage.size(), 0);
        }
        sent = send(clientSocket, message.data(), message.size(), 0);
        if (sent < 0)
          spdlog::error("Could not send the initial messages");
      }
      continue;
    }

    spdlog::info("Message from {}: {}", username, buffer);

    receivingThreadMutex.lock();

    string bufferString = "[" + username + "] " + string(buffer);
    broadcastMessage(bufferString, clientSocket);

    receivingThreadMutex.unlock();
  }
}

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

  vector<thread*> clientThreads;

  while (true) { 
    sockaddr_in clientAddress;
    socklen_t clientAddressLen = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (sockaddr*)&clientAddress, &clientAddressLen);
    if (clientSocket == -1) {
      spdlog::error("Failed to accept the connection.");
      return; 
    }

    thread* clientThread = new thread(receivingThreadCallback, clientSocket);
    clientThreads.push_back(clientThread);
    connectedClientSockets.insert(clientSocket);
    spdlog::info("Accepted the connection from {} : {}.", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));
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
