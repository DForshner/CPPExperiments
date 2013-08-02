#include <iostream>
#include <functional>

// Compiler: Microsoft Visual C++ Compiler Nov 2012 CTP (v120_CTP_Nov2012)

using namespace std;

void main()
{
  std::cout << "Lambda Expressions" << std::endl;

  // Lambda expressions allow you to create functions on the fly.
  // The capture of the enclosing variable by the lambda expression is called closure.

  int x = 1, y = 2;

  // [...] is the capture specifier and shows how free variables will be captured.
  // [] empty - The body of the lambda expression can't reference any variables outside of its scope.
  // [=] - Capture by value
  // [&] - Capture by reference

  // Displays the values of free variables x and y.
  // For simplicity lambdas can be created using auto.
  // x is captured once by value so it will always be its value at capture (1).
  // y is captured by reference so it can be changed by side effects will be the current value of y.
  auto display = [x, &y] () { std::cout << "In  - x: " << x << " y: " << y << std::endl; };

  display();
  std::cout << "Out - x: " << x << " y: " << y << std::endl << std::endl;

  x = 100;
  y = 200;

  // Captures y by reference so y gets incremented
  auto func2 = [&y] () { y++; };
  func2();

  display(); // Displays 1, 201
  std::cout << "Out - x: " << x << " y: " << y << std::endl << std::endl; // Displays 100, 201

  // Captures y by value.
  // The mutable keyword allows the lambda to change y inside the body of the lambda.  Otherwise it's considered const.
  auto func3 = [y] () mutable { y++;};
  //auto func3failure = [y] () { y ++; }; // Gives "by-value capture cannot be modified by non-mutable lambda" compiler error
  func3();

  display(); // Displays 1, 201
  std::cout << "Out - x: " << x << " y: " << y << std::endl << std::endl; // Displays 100, 201

  // Captures everything by reference
  auto func4 = [&] () { y++; x++; };
  func4();

  display(); // Displays 1, 202
  std::cout << "Out - x: " << x << " y: " << y << std::endl << std::endl; // Displays 101, 202

  
  std::cout << std::endl << " -- Recursion -- " << std::endl;
  
  // Lambda expressions can be created using std::function<>
  // Captures lambda function by reference
  // ( params ) is the parameter list
  // -> rettype is the optional return type specifier
  std::function<int (int)> factorial = [&factorial] (int x) -> int {
    std::cout << x << ", ";
    
    // If x is not zero recursively call next level
    if (x == 0) return 1;
    return x * factorial(x - 1);
  };

  auto res = factorial(10);
  std::cout << std::endl << "res: " << res << std::endl;
}