#include "proxy.h"

using namespace std;
using json = nlohmann::json;

namespace Proxy {

thread* proxyThread;

void proxyThreadCallback() { 
  int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (clientSocket < 0) {
    spdlog::error("Couldn't create the socket that connects to the client.");
    return;
  }

  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket < 0) {
    spdlog::error("Couldn't create the socket that connects to the server.");
    return;
  }

  char buffer[65536];
  sockaddr_in sourceAddress{};
  socklen_t sourceAddressLength = sizeof(sourceAddress);
  while (true) {
    ssize_t receiveLength = recvfrom(clientSocket, buffer, sizeof(buffer), 0, (sockaddr*)&sourceAddress, &sourceAddressLength);
    if (receiveLength < 0) {
      spdlog::error("Couldn't recieve from the client");
      break; 
    }

    cout << (char*)buffer << endl;
    spdlog::info("Received from {}", inet_ntoa(sourceAddress.sin_addr));
  }
}

void create() {
  thread* proxy = new thread(proxyThreadCallback);
  proxyThread = proxy;
}

void stop() {
  if (proxyThread->joinable())
    proxyThread->join();
  delete proxyThread;
}

}
