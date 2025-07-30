// TODO: Get the cin stuff to work
// TODO: When a new user joins add in code to "fill them in" by giving them a full array of the messages so far

#include "windows/chat.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>

using namespace std;
using json = nlohmann::json;
using namespace ftxui;

namespace Chat {

vector<string> messages;
mutex mtx;

void displayMessages() {
  system("clear");
  mtx.lock();
  for (string message : messages)
    cout << message << endl;
  mtx.unlock();
  cout << "Input message: ";
}

void receive(int socket) {
  char buffer[1024] = { 0 };
  int bytesRecieved = recv(socket, buffer, sizeof(buffer), 0);
  if (bytesRecieved > 0){
    buffer[bytesRecieved] = '\0';
    mtx.lock();
    messages.push_back(string(buffer));
    mtx.unlock();
    displayMessages();
  }
}

void join(int PORT) {
  system("clear");

  int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

  if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
    spdlog::error("Could not connect to the client.");
    return;
  }
  string stringMessage = "";

  thread receivingThread(receive, clientSocket);  

  while (stringMessage != "exit") { 
    ssize_t sent = send(clientSocket, stringMessage.data(), stringMessage.size(), 0);
    if (sent < 0) {
      spdlog::error("Could not send.");
      break;
    }
    if (stringMessage != "")
      messages.push_back(stringMessage);
    displayMessages();
    cin >> stringMessage;
  }

  if (receivingThread.joinable())
    receivingThread.join();
  close(clientSocket);
}

}

