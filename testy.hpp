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
    testSuite.printTitle("Testy - test module "#name); \
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
#define it(text, ...) \
  {text, [] () { \
      __VA_ARGS__ \
      return true; \
    }}

/**
 * @macro test
 * Test if the given expr is true.
 */
#define test(expr) if (!(expr)) return false;

/**
 * @macro testRange
 * Test if the given expr is in the given range.
 */
#define testRange(expr, begin, end) \
  { \
    auto const &val = expr; \
    if (val > end || val < begin) \
      return false; \
  }


/**
 * @macro testThrow
 * Test if the given `expr` throw the given `except`.
 */
#define testThrow(expr, except) try { expr } catch (except) {}

/**
 * @enum Theme
 * Display theme.
 */
enum Theme { Default, Classic };

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

  /**
   * Set the current print theme.
   */
  inline void setTheme(Theme theme);

  /**
   * Print the title of the test suite.
   */
  inline void printTitle(std::string const &title);

  /**
   * Print a subtitle.
   */
  inline void printSubtitle(std::string const &subtitle);

  /**
   * Print a fail label.
   */
  inline void printFail(bool isFinal = false);

  /**
   * Print a success label.
   */
  inline void printSuccess(bool isFinal = false);

  /**
   * Clear the print format (useful with colors for instance).
   */
  inline void printClear();

  /**
   * Register a new unit test.
   * @param desc The description of this unit.
   * @param unit The unit which contains all tests.
   */
  inline void addUnit(std::string const &desc, Unit const &unit);

  /**
   * Return all unit tests.
   * @return Returns the number of failures or 0 on success.
   */
  inline int run();
 private:
  std::list<std::pair<std::string, Unit>> _units;
};

void TestSuite::printTitle(std::string const &title) {
    std::cout << std::endl << "  \e[1m" << title << std::endl;
    std::cout << "  ";
    for (size_t i = 0; i < title.size(); ++i)
      std::cout << "=";
    std::cout << "\e[m"<< std::endl;
}

void TestSuite::printSubtitle(std::string const &subtitle) {
  std::cout << "  \e[m## " << subtitle << std::endl << std::endl;
}

void TestSuite::printFail(bool) {
  std::cout << "\e[0;31m✗ ";
}

void TestSuite::printSuccess(bool isFinal) {
  std::cout << "\e[0;32m✓ ";
  if (!isFinal)
    std::cout << "\e[1;30m";
}

void TestSuite::printClear() {
  std::cout << "\e[m";
}

void TestSuite::addUnit(std::string const &desc,
                               TestSuite::Unit const &unit) {
  _units.push_back(std::make_pair(desc, unit));
}

int TestSuite::run() {
  std::chrono::steady_clock::time_point prev;
  int fail = 0;
  int total = 0;
  size_t duration = 0;

  std::cout << std::endl;
  for (auto &unit : _units) {

    // Display the test description
    printSubtitle(unit.first);

    for (auto &test : unit.second) {

      // Run the test and display the fail or success message

      prev = std::chrono::steady_clock::now();
      std::cout << "    ";
      try {
        if (!test.second()) { // false if callback return false
          ++fail;
          printFail();
        } else { // succeed otherwise
          printSuccess();
        }
      } catch (...) { // fail if an unexpected exception is thrown.
        ++fail;
        printFail();
      }

      // and duration of the function call

      size_t delta = (std::chrono::steady_clock::now() - prev).count() / 1000;
      duration += delta;
      std::cout << test.first << " (" << delta << "ms)" << std::endl;
      ++total;
    }
    std::cout << std::endl;
  }

  // Display the result of the tests

  if (fail) {
    std::cout << "  ";
    printFail();
    std::cout << fail << " of " << total << " tests failed "
              << "(" << duration << "ms)";
  } else {
    std::cout << "  ";
    printSuccess(true);
    std::cout << total << " tests completed "
              << "(" << duration << "ms)";
  }
  printClear();
  std::cout << std::endl << std::endl;

// Wait for keyboard press on windows to keep the output console opened.
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
  std::cout << "  [ Press any key to quit ]" << std::endl << std::endl;
  std::cin.get();
#endif

  return fail;
}

}
