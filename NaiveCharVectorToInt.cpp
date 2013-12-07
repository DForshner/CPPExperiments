// Naive implementation of code to convert a vector of numeric chars to an int.
//
// Assumes plain ASCII chars and doesn't handle overflow.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

bool is_number(char c) {
  auto code = unsigned(c);
  return (code >= 48 && code <= 57);
}

// Assumes plain ASCII chars with MSD first. 
unsigned naive_to_int(const vector<char> &vec){
  unsigned base = 1;
  unsigned total = 0;
  unsigned prev_total = 0;

  // Note: if (auto i = vec.size() - 1; i >= 0; i--) is used i could 
  // roll over to large positive leading to infinite loop.
  for (auto i = vec.size(); i > 0; i--) {
    auto element = vec[i - 1];

    // Check valid numeric char
    if (!is_number(element))
      throw std::exception("string contains non numeric ASCII char");

    auto val = (unsigned)vec[i - 1] - 48;
    total += val * base;
    base *= 10;
  }

  return total;
}

void main() {
  // Test simple conversion
  auto a = vector<char> { '1', '2', '3', '8', '9', '0', '9' };
  auto a_value = naive_to_int(a);
  cout << endl << '"' << "1238909" << '"' << " = " << a_value << endl;

  // Test invalid char exception
  auto b = vector<char> { '1', 'A', '3' };
  try {
      auto b_value = naive_to_int(b);
      cout << endl << '"' << "12345678909" << '"' << " = " << b_value << endl;
  }
  catch (std::exception e) {
    cout << endl << "Caught: " << e.what() << endl;
  }

  cout << endl << "[Press enter to exit]";
  cin.ignore();
}