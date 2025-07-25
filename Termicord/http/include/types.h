#ifndef TYPES_H
#define TYPES_H

struct Result {
  int responseCode;
  std::string json;

  Result() = default;
  Result(int responseCode, std::string json) : responseCode(responseCode), json(json) {}
};

#endif 
