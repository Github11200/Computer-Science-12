#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <vector>
#include <iostream>
#include <spdlog/spdlog.h>
#include <type_traits>
#include <magic_enum/magic_enum.hpp>

using namespace std;

namespace Input {

inline void getStringInput(string message, string& input) {
  cout << message;
  cin >> input;
}

template <typename T>
void getNumericInput(string message, T& input) {
  while (true) {
    string temp;
    cout << message;
    cin >> temp;
    if (is_integral<T>::value) {
      try {
        input = stoi(temp);
        return;
      } catch (const exception& e) {
        cout << "Invalid input. Please enter an integer." << endl;
      }
    } else if (is_floating_point<T>::value) {
      try {
        input = stod(temp);
        return;
      } catch (const exception& e) {
        cout << "Invalid input. Please enter a floating point value." << endl;
      }
    } 
  }
}

template <typename T>
void getBoundedNumericInput(string message, T& input, T lower, T upper) { 
  while (true) {
    getNumericInput<T>(message, input);
    if (input > upper || input < lower)
      cout << "Invalid input. The input must be between " + to_string(lower) + " and " + to_string(upper) + "." << endl;
    else return; 
  }
}

template <typename Enum>
void getOption(string message, vector<string> options, int& input) { 
  try {
    size_t enumLength = magic_enum::enum_count<Enum>(); 
    cout << message << endl;
    for (int i = 1; i <= options.size(); ++i) 
      cout << "  (" << to_string(i) << ") " << options[i - 1] << endl;  
    Input::getBoundedNumericInput<int>("Input: ", input, 1, enumLength);
  } catch (const exception& e) {
    cout << "Error: " << e.what() << endl;
  }
}

}

#endif
