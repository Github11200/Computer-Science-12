#include <iostream>
#include <vector>
#include <string>
#include <stduuid/uuid.h>

struct User {
  std::string username;
  vector<string> servers;
  vector<string> friends;
}

void getUser();
void getUsers();
