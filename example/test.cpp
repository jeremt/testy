
#include <stdexcept>
#include "testy.hpp"
#include "Calculator.hpp"

Suite("myModule", {

  describe("Calculator",

    it("Should add numbers correctly",
      test(Calculator::instance.add(1, 2) == 3)
      test(Calculator::instance.add(-1, 2) == 1)
      test(Calculator::instance.add(42, 42) == 84)
      testRange(Calculator::instance.add(2, 2), 3, 5)
    ),

    it("Should not be a number",
      test(Calculator::instance.isNumber("test") == false)
    ),

    it("Should fail", test(false == true && 42 != 42)),

    it("Should take time",
      Calculator::instance.bigCalc();
    )

  )

  describe("GlobalTests",

    it("Should return true", ),

    it("Shoud throw a runtime error",
      testThrow(throw std::runtime_error("test");, std::runtime_error)
    ),

    it ("Should fail by throwing the wrong exception",
      testThrow(throw std::invalid_argument("test");, std::out_of_range)
    )

  )

  example("Simple example",
    std::cout << "My Simple example..." << std::endl;
  )

})
