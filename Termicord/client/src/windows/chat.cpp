// TODO: When a new user joins add in code to "fill them in" by giving them a
// full array of the messages so far
// TODO:

#include "windows/chat.h"

using namespace std;
using json = nlohmann::json;

termios orig_termios;

void disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
  cout << "\033[?25h"; // Show the cursor
}

void enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disableRawMode);

  termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON);
  raw.c_iflag &= ~(IXON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

  cout << "\033[?25l"; // Hide the cursor
}

void moveCursor(int x, int y) { cout << "\033[" << y << ";" << x << "H"; }

namespace Chat {

vector<string> messages;
mutex mtx;
bool running = true;

void redraw(string &input) {
  mtx.lock();
  system("clear");

  int row = 1;
  for (const auto &message : messages) {
    moveCursor(1, row++);
    cout << message;
  }
  moveCursor(1, row + 1);
  cout << "> " << input << flush;
  moveCursor(3 + input.size(), row + 1);
  mtx.unlock();
}

void receive(int socket, string &input) {
  while (true) {
    char buffer[1024] = {0};
    int bytesRecieved = recv(socket, buffer, sizeof(buffer), 0);
    if (bytesRecieved > 0) {
      buffer[bytesRecieved] = '\0';
      mtx.lock();
      messages.push_back(string(buffer));
      mtx.unlock();
      // cout << "I RECEIVED" << endl;
      redraw(input);
    }
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

  if (connect(clientSocket, (struct sockaddr *)&serverAddress,
              sizeof(serverAddress)) == -1) {
    spdlog::error("Could not connect to the client.");
    return;
  }

  enableRawMode();

  string input = "";
  redraw(input);

  thread receivingThread(receive, clientSocket, ref(input));
  while (true) {
    char c;
    if (read(STDIN_FILENO, &c, 1) <= 0)
      break;

    if (c == '\n' && !input.empty()) {
      ssize_t sent = send(clientSocket, input.data(), input.size(), 0);
      if (sent < 0) {
        spdlog::error("Could not send.");
        break;
      }

      mtx.lock();
      messages.push_back(input);
      mtx.unlock();
      input = "";
      redraw(input);
    } else if ((c == 8 || c == 127) &&
               !input.empty()) { // They press backspace or delete
      input.pop_back();
      redraw(input);
    } else if (isprint(c)) {
      input += c;
      redraw(input);
    }
  }

  if (receivingThread.joinable())
    receivingThread.join();
  close(clientSocket);
  disableRawMode();
}

} // namespace Chat
