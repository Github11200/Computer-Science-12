#include "windows/chat.h"

using namespace std;
using json = nlohmann::json;
using namespace ftxui;

namespace Chat {

vector<string> messages;

void displayMessages() {
  system("clear");
  for (string message : messages)
    cout << message << endl;
  cout << "Input message: ";
}

void receive(int socket) {
  char buffer[1024] = { 0 };
  int bytesRecieved = recv(socket, buffer, sizeof(buffer), 0);
  if (bytesRecieved > 0){
    buffer[bytesRecieved] = '\0';
    messages.push_back(string(buffer));
    displayMessages();
  }
}

void join(int PORT) {
  system("clear");

  // // Create a simple document with three text elements.
  // Element document = hbox({
  //   text("left")   | border,
  //   text("middle") | border | flex,
  //   text("right")  | border,
  // });
  //
  // // Create a screen with full width and height fitting the document.
  // auto screen = Screen::Create(
  //   Dimension::Full(),       // Width
  //   Dimension::Fit(document) // Height
  // );
  //
  // // Render the document onto the screen.
  // Render(screen, document);
  //
  // // Print the screen to the console.
  // screen.Print();
  //
  // // auto screen = ScreenInteractive::FitComponent();
  // // std::string content= "";
  // // std::string placeholder = "placeholder";
  // // Component input = Input({
  // //   .content = &content,
  // //   .placeholder = &placeholder,
  // // });
  // // screen.Loop(input);
  //
  // return;
  int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

  connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
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
