#include "windows/auth.h"

using namespace std;
using json = nlohmann::json;

namespace Auth {

void init() {
  int authTypeInput = 0;
  Input::getOption<AuthType>("Would you like to login or sign up?", vector<string>({"Login", "Sign Up"}), authTypeInput);
  if (authTypeInput == AuthType::LOGIN)
    login();
  else if (authTypeInput == AuthType::SIGN_UP)
    signUp();
}

void login() {
  while (true) {
    string username, password;
    Input::getStringInput("Username: ", username);
    Input::getStringInput("Password: ", password);
    
    Requests::Request request("/getUser", json::parse("{ \"username\": \"" + username + "\" }"));      
    Requests::APIResult result = Requests::sendRequest(request);

    if (result.code == Requests::ResponseCode::SUCCESS) {
      User user = result.data.get<User>();

      if (user.password == password)
        return;
      int nextStepInput = 0;
      Input::getOption<NextStep>("Password is incorrect. Would you like to try again or exit?", vector<string>({"Try again", "Exit"}), nextStepInput);
      
      if (nextStepInput == NextStep::RETRY)
        continue;
      else if (nextStepInput == NextStep::EXIT)
        return;
    } else if (result.code == Requests::ResponseCode::INTERNAL_SERVER_ERROR) {
      int nextStepInput = 0;
      Input::getOption<NextStep>("Username not found. Would you like to try again or create an account?", vector<string>({"Try again", "Sign Up"}), nextStepInput);

      if (nextStepInput == NextStep::RETRY)
        continue;
      else if (nextStepInput == NextStep::EXIT) {
        signUp();
        return;
      } 
    } 
  }
}

void signUp() {
  while (true) {
    system("clear");
    string username, password = "";
    Input::getStringInput("New Username: ", username);
    Input::getStringInput("New password: ", password, 8);

    User newUser;
    newUser.password = password;
    newUser.friends = vector<string>();
    newUser.servers = vector<string>();

    json jsonUser(newUser);
    jsonUser["username"] = username;
    Requests::Request request("/addUser", jsonUser);
    Requests::APIResult result = Requests::sendRequest(request);

    if (result.code == Requests::ResponseCode::SUCCESS) 
      return;
    else if (result.code == Requests::ResponseCode::INTERNAL_SERVER_ERROR) {
      int nextStepInput = 0;
      Input::getOption<NextStep>("There was an internal server error. Would you like to try again or exit?", vector<string>({"Try again", "Exit"}), nextStepInput);
      if (nextStepInput == NextStep::RETRY) continue;
      else if (nextStepInput == NextStep::EXIT) return;
    }
  }
}

}
