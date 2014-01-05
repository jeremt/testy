
#pragma once

class Calculator {
public:
  Calculator();
  ~Calculator();
  void bigCalc();
  template<typename Type>
  Type add(Type a, Type b);
  template<typename Type>
  bool isNumber(Type const &value);
public:
  static Calculator instance;
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
