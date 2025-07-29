#include "windows/auth.h"

using namespace std;
using json = nlohmann::json;

namespace Auth {

string username;
User currentUser;

void init() {
  system("clear");
  AuthType authTypeInput; 
  Input::getOption<AuthType>("Would you like to login or sign up?", vector<string>({"Login", "Sign Up"}), authTypeInput);
  if (authTypeInput == AuthType::LOGIN)
    login();
  else if (authTypeInput == AuthType::SIGN_UP)
    signUp();
}

void login() {
  system("clear");
  while (true) {
    string username, password;
    Input::getStringInput("Username: ", username);
    Input::getStringInput("Password: ", password);
   
    json jsonObject = {
      {"username", username}
    };
    Requests::Request request("/getUser", jsonObject);
    Requests::APIResult result = Requests::sendRequest(request);

    if (result.code == Requests::ResponseCode::SUCCESS) {
      User user = result.data.get<User>();

      if (user.password == password) {
        Auth::currentUser = user;
        return;
      }
        
      NextStep nextStepInput;
      Input::getOption<NextStep>("Password is incorrect. Would you like to try again or exit?", vector<string>({"Try again", "Exit"}), nextStepInput); 

      if (nextStepInput == NextStep::RETRY)
        continue;
      else if (nextStepInput == NextStep::EXIT)
        return;
    } else if (result.code == Requests::ResponseCode::INTERNAL_SERVER_ERROR) {
      NextStep nextStepInput; 
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
    // system("clear");
    string username, password = "";
    Input::getStringInput("New Username: ", username);
    Input::getStringInput("New password: ", password, 8);

    try {
      User newUser;
      newUser.password = password;
      newUser.friends = vector<string>();
      newUser.servers = vector<string>();
      newUser.name = username;

      json jsonUser(newUser);
      jsonUser["username"] = username;
      cout << jsonUser.dump(2) << endl;
      cpr::Response r = cpr::Post(
        cpr::Url{"http://localhost:8000/addUser"},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Body{jsonUser.dump()}
      );

      if (r.status_code == Requests::ResponseCode::SUCCESS) {
        Auth::currentUser = newUser;
        return;
      }
      else if (r.status_code == Requests::ResponseCode::INTERNAL_SERVER_ERROR) {
        NextStep nextStepInput; 
        Input::getOption<NextStep>("There was an internal server error. Would you like to try again or exit?", vector<string>({"Try again", "Exit"}), nextStepInput);
        if (nextStepInput == NextStep::RETRY) continue;
        else if (nextStepInput == NextStep::EXIT) return;
      }
    } catch (const exception& e) {
      cout << "Couldn't add the user." << endl;
      cout << e.what() << endl;
    }
  }
}

}
