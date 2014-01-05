testy
=====

Testy is a micro C++ unit test tool.

Usage
-----

Simple include testy.hpp into a c++ file and compile with your file to test.

```c++

#include "testy.hpp"
#include "Calculator.hpp"

Suite("myModule", {

  describe("Calculator",

    it("Should equals to 4",
      return Calculator::getInstance().add(1, 2) == 3;
    ),

    it("Should not be a number",
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

```

Then, execute your program and show the following output:

![myImage](example.png)

TODO
----

- Add testTime macro to test `expr` duration.
- Add testOutput macro to test outputs such as std::cout or printf
- Any ideas?;)
