
#include "testy.hpp"
#include "Calculator.hpp"

Suite("myModule", {

  describe("Calculator",

    it("Should equals to 4",
      return Calculator::getInstance().add(1, 2) == 3;
    ),

    it("The string should not be a number",
      return Calculator::getInstance().isNumber("test") == false;
    ),

    it("Should fail",
      return false;
    ),

    it("Should take time",
      Calculator::getInstance().bigCalc();
      return true;
    )

  )

  describe("Useless tests",

    it("Should return true",
      return true;
    )

  )

})
