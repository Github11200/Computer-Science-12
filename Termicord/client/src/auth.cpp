#include "auth.h"

using namespace std;
using json = nlohmann::json;

namespace Auth {

void authInit() {
  int authTypeInput = 0;
  Input::getOption<AuthType>("Would you like to login or sign up?", vector<string>({"Login", "Sign Up"}), authTypeInput);
  authTypeInput = 1;
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
      int nextStepInput = 0;
      Input::getOption<NextStep>("Password is incorrect. Would you like to try again or exit?", vector<string>({"Try again", "Exit"}), nextStepInput);
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

}

}
