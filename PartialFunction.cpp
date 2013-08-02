#include <iostream>
#include <functional>

// Compiler: Microsoft Visual C++ Compiler Nov 2012 CTP (v120_CTP_Nov2012)

using namespace std;

void main()
{
  std::cout << std::endl << "Partial Function Application" << std::endl;

  // A partial function is a function that is called with fewer arguments than it's argument list requires.
  // A lambda is returned with the remainder of the arguments.

  // Std::bind takes a function pointer and then a sequence of values or placeholder 
  // (std::placeholders) as arguments and returns a function object.

  // Repeatable call f using the value returned from the previous call.
  // [] Empty capture - Lambda can't capture any variables outside of its scope.
  auto repeat = [](int n, double y, std::function<double(double)>f) {
    while (n-- > 0) {
      y = f(y);
    }
    return y;
  };

  // std::bind returns a callable function object.
  // The relative position of the values & placeholders corresponds to the position of the arguments of
  // the function repeat.  The placeholders correspond to the argument of the function object returned by
  // std::bind.
  auto rpl = std::bind(repeat, 
    std::placeholders::_1, // The first argument is passed to the repeat function as both for the 
    std::placeholders::_1, // number of times to repeat and the initial value.
    std::placeholders::_2);

  std::function<double(double)> times2 = [] (double x) {
    return 2 * x; 
  };

  std::cout << "Result 1: " << rpl(15, times2) << std::endl;

  // std:bind can also be used without placeholders
  auto noPlaceholders = std::bind(repeat, 15, 15, times2);
  std::cout << "Result 2: " << noPlaceholders() << std::endl;
}
