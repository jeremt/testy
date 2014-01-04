
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
    testSuite.displayTitle("Testy - test module "#name); \
    std::cout << std::endl; \
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
  inline void displayTitle(std::string const &title);
  inline void displaySubtitle(std::string const &subTitle);
  inline void addUnit(std::string const &desc, Unit const &unit);
  inline int run();
 private:
  std::list<std::pair<std::string, Unit>> _units;
};

inline void TestSuite::displayTitle(std::string const &title) {
    std::cout << std::endl << "  " << title << std::endl;
    std::cout << "  ";
    for (size_t i = 0; i < title.size(); ++i)
      std::cout << "=";
}

inline void TestSuite::displaySubtitle(std::string const &subTitle) {
  std::cout << "  \e[m## " << subTitle << std::endl << std::endl;
}

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
    displaySubtitle(unit.first);

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

  if (fail) {
    std::cout << "  \e[0;31m✗ " << fail << " of "
              << total << " tests failed "
              << "(" << duration << "ms)";
  } else {
    std::cout << "  \e[0;32m✓ " << total
              << " tests completed "
              << "(" << duration << "ms)";
  }
  std::cout << "\e[m" << std::endl << std::endl;
  return fail;
}

}
