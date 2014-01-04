
#include <typeinfo>
#include "Calculator.hpp"

Calculator Calculator::_instance;

Calculator::Calculator() {}

Calculator::~Calculator() {}

Calculator &Calculator::getInstance() {
  return _instance;
}
