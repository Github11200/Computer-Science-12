#include "utils.h"

using namespace std;

string generateUUID() {
  uuid_t uuid;
  char uuid_str[37];

  // Generate the uuid id and then convert it to a string
  uuid_generate(uuid);
 
  uuid_unparse_lower(uuid, uuid_str);
  return string(uuid_str);
}
