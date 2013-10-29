
#include "testy.hpp"

class Calculator {
public:
  Calculator();
  ~Calculator();
  static Calculator &getInstance();
  template<typename Type>
  Type add(Type a, Type b);
  template<typename Type>
  bool isNumber(Type const &value);
private:
  static Calculator _instance;
};

Calculator Calculator::_instance;

Calculator::Calculator() {}

Calculator::~Calculator() {}

Calculator &Calculator::getInstance() {
  return _instance;
}

template<typename Type>
Type Calculator::add(Type a, Type b) {
  return a + b;
}

template<typename Type>
bool Calculator::isNumber(Type const &value) {
  return typeid(int) == typeid(value) ||
         typeid(float) == typeid(value) ||
         typeid(double) == typeid(value);
}

int main() {

  testy::add("Calculator", {
    {"Should equals to 4", [] () {
      return Calculator::getInstance().add(1, 2) == 3;
    }},
    {"The string should not be a number", [] () {
      return Calculator::getInstance().isNumber("test") == false;
    }},
    {"Should fail", [] () {
      return false;
    }}
  });

  testy::add("Useless tests", {
    {"Should return true", [] () {
      return true;
    }}
  });

  return testy::run();
}