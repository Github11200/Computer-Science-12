#ifndef ROUTING_H
#define ROUTING_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <any>
#include <functional>

struct Route {
  std::string route;
  std::function<std::any()> callback;

  Route() = default;
  Route(std::string route, std::function<std::any()> callback) : route(route),
                                                                 callback(callback) {} 
};

class Routing {
private:
  std::unordered_map<std::string, Route> routes; 

public:
  Routing();
  void addRoute(Route route);
  Route getRoute(std::string route); 
  std::string getRouteNameFromHeader(std::string header);
};

#endif
