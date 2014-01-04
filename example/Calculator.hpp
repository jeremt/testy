
#pragma once

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
