// TODO: When a new user joins add in code to "fill them in" by giving them a
// full array of the messages so far
// TODO:

#include "windows/chat.h"
#include "windows/auth.h"
#include "windows/home.h"
#include <asm-generic/ioctls.h>
#include <curses.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#define SHOW_CURSOR "\033[?25h"
#define HIDE_CURSOR "\033[?25l"

using namespace std;
using json = nlohmann::json;

termios orig_termios;

void disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
  cout << SHOW_CURSOR;
}

void enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disableRawMode);

  termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON);
  raw.c_iflag &= ~(IXON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

  cout << HIDE_CURSOR;
}

void moveCursor(int x, int y) { cout << "\033[" << y << ";" << x << "H"; }

namespace Chat {

vector<string> messages;
mutex mtx;
atomic<bool> running(true);

void redraw(string &input) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int row = w.ws_row - 1;

  mtx.lock();
  system("clear");

  for (int i = messages.size() - 1; row > 0 && i >= 0; --i) {
    moveCursor(1, row--);
    cout << messages[i];
  }
  moveCursor(1, w.ws_row);
  cout << "> " << input << flush;
  moveCursor(3 + input.size(), w.ws_row);
  mtx.unlock();
}

void receive(int socket, string &input) {
  while (Chat::running) {
    char buffer[1024] = {0};
    int bytesRecieved = recv(socket, buffer, sizeof(buffer), 0);
    if (bytesRecieved > 0) {
      buffer[bytesRecieved] = '\0';
      vector<string> seperatedMessageStrings = splitString(string(buffer), '\n');
      for (int i = 0; i < seperatedMessageStrings.size(); ++i) {
        string messageString = seperatedMessageStrings[i];

        // If the username sent is the same as the current user's then just change it to [You]
        // ex. "[Github11200] Hello" --> "[You] Hello", assuming the current username is Github11200
        string messageUsername = ""; 
        int j = 1;
        for (; messageString[j] != ']'; ++j)
          messageUsername.push_back(messageString[j]);
        if (messageUsername == Auth::currentUser.username)
          messageString = "[You] " + messageString.substr(j + 2, messageString.size() - (j + 2));

        mtx.lock();
        messages.push_back(messageString);
        mtx.unlock();
        redraw(input);
      }
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

  Chat::running = true;
  thread receivingThread(receive, clientSocket, ref(input));
  while (Chat::running) {
    char c;
    if (read(STDIN_FILENO, &c, 1) <= 0)
      break;

    if (c == '\n' && !input.empty()) {
      if (input == "/exit") {
        Chat::running = false; 
        shutdown(clientSocket, SHUT_RDWR);
        break;
      }
      string inputToBeSent = "[" + Auth::currentUser.username + "] " + input;
      ssize_t sent = send(clientSocket, inputToBeSent.data(), inputToBeSent.size(), 0);
      if (sent < 0) {
        spdlog::error("Could not send.");
        break;
      }

      mtx.lock();
      messages.push_back("[You] " + input);
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

  disableRawMode();
  if (receivingThread.joinable())
    receivingThread.join();
  close(clientSocket);
  Home::init();
}

} // namespace Chat
