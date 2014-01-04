
#include <string>
#include <typeinfo>
#include "Calculator.hpp"
#include <iostream>

Calculator Calculator::_instance;

Calculator::Calculator() {}

Calculator::~Calculator() {}

Calculator &Calculator::getInstance() {
  return _instance;
}

void Calculator::bigCalc() {
  size_t iter = 42;
  std::string str;

  for (size_t i = 0; i < iter; ++i) {
    str += "f(x) = ax + b";
    for (size_t j = 0; j < iter; ++j) {
      str += "g(x) = x^2";
      for (size_t k = 0; k < iter; ++k) {
        str.substr(str.size() / 2);
      }
    }
  }
}
