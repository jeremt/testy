
#pragma once

#include <list>
#include <unordered_map>
#include <string>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <functional>
#include <unistd.h>

/**
 * @namespace testy
 * Simple tool to easly manage unit tests.
 */
namespace testy {

/**
 * @macro
 * The macro used to create the test suite.
 */
#define Suite(name, code) \
  int main() { \
    testy::TestSuite testSuite; \
    std::cout << std::endl \
              << "  \e[1mTesty - test module "#name"\e[m" \
              << std::endl; \
    code \
    return testSuite.run(); \
  }

/**
 * @macro
 * Describe one entity of the suite.
 */
#define describe(name, ...) \
  testSuite.addUnit(name, { \
    __VA_ARGS__ \
  });

/**
 * @macro
 * Test one action of the suite.
 */
#define it(text, code) \
  {text, [] () { \
      code \
    }}

#define test(expr) return expr;

/**
 * TestSuite
 * Simple test suite in which you can register units and run all unit tests.
 */
class TestSuite {
 public:
  /**
   * @typedef Unit
   * Describe a unit to test.
   */
  typedef std::list<std::pair<std::string, std::function<bool()>>> Unit;
  TestSuite() {}
  ~TestSuite() {}
  inline void addUnit(std::string const &desc, Unit const &unit);
  inline int run();
 private:
  std::list<std::pair<std::string, Unit>> _units;
};

/**
 * Register a new unit test.
 * @param desc The description of this unit.
 * @param unit The unit which contains all tests.
 */
inline void TestSuite::addUnit(std::string const &desc,
                               TestSuite::Unit const &unit) {
  _units.push_back(std::make_pair(desc, unit));
}

/**
 * Return all unit tests.
 * @return Returns the number of failures or 0 on success.
 */
inline int TestSuite::run() {
  std::chrono::steady_clock::time_point prev;
  int fail = 0;
  int total = 0;
  size_t duration = 0;

  std::cout << std::endl;
  for (auto &unit : _units) {

    // Display the test description

    std::cout << "  \e[1;36m► " << unit.first << std::endl << std::endl;

    for (auto &test : unit.second) {

      // Run the test and display the fail or success message

      prev = std::chrono::steady_clock::now();
      std::cout << "    ";
      if (!test.second()) {
        ++fail;
        std::cout << "\e[0;31m✗ ";
      } else {
        std::cout << "\e[0;32m✓ \e[1;30m";
      }

      // and duration of the function call

      size_t delta = (std::chrono::steady_clock::now() - prev).count() / 1000;
      duration += delta;
      std::cout << test.first << " ("
                << std::fixed << delta
                << "ms)" << std::endl;
      ++total;
    }
    std::cout << std::endl;
  }

  // Display the result of the tests

  std::cout << "  \e[35m";
  if (fail) {
    std::cout << "✗ " << fail << " of "
              << total << " tests failed "
              << "(" << duration << "ms)";
  } else {
    std::cout << "✓ " << total
              << " tests completed "
              << "(" << duration << "ms)";
  }
  std::cout << "\e[m" << std::endl << std::endl;
  return fail;
}

}
