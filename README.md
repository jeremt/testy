testy
=====

Testy is a micro C++ unit test tool.

Example
-------

Simple add your test by category, with a list of test functions and descriptions.

```c++

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

```

The previous code will generate the following output:

![myImage](example.png)
