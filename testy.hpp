
#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <functional>

/**
 * @namespace testy
 * Simple tool to easly manage unit tests.
 */
namespace testy {

/**
 * @typedef Unit
 * The data type for one unit.
 */
typedef std::unordered_map<std::string, std::function<bool()>> Unit;

/**
 * All units.
 */
std::unordered_map<std::string, Unit> units;

/**
 * Register a new unit test.
 * @param desc The description of this unit.
 * @param unit The unit which contains all tests.
 */
inline void add(std::string const &desc, Unit const &unit) {
  units[desc] = unit;
}

/**
 * Return all unit tests.
 * @return Returns the number of failures or 0 on success.
 */
inline int run() {
  std::chrono::time_point<std::chrono::system_clock> start;
  std::chrono::time_point<std::chrono::system_clock> t;
  std::chrono::duration<double> d;
  int fail = 0;
  int total = 0;

  start = std::chrono::system_clock::now();
  std::cout << std::endl;
  for (auto &unit : units) {
    std::cout << "  \e[1;36m► " << unit.first << std::endl << std::endl;
    for (auto &test : unit.second) {
      t = std::chrono::system_clock::now();
      std::cout << "    ";
      if (!test.second()) {
        ++fail;
        std::cout << "\e[0;31m✗ ";
      } else {
        std::cout << "\e[0;32m✓ \e[1;30m";
      }
      d = std::chrono::system_clock::now() - t;
      std::cout << test.first << " (" << std::fixed << d.count() << "s)" << std::endl;
      ++total;
    }
    std::cout << std::endl;
  }
  std::cout << "  \e[35m";
  d = std::chrono::system_clock::now() - start;
  if (fail) {
    std::cout << "✗ " << fail << " of " << total << " tests failed " << "(" << d.count() << "ms)";
  } else {
    std::cout << "✓ " << total << " tests completed " << "(" << d.count() << "ms)";
  }
  std::cout << "\e[m" << std::endl << std::endl;
  return fail;
}

}