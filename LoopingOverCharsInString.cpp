// Loop over chars in a string.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>;

using namespace std;

void display(const string& str) {
  cout << endl << "C++11 Ranged based for loop" << endl;
  for (const char &c: str) // access by reference to avoid copying
    cout << c << ",";

  cout << endl << "Using iterators" << endl;
  for (auto iter = str.cbegin(); iter != str.cend(); ++iter) // .cbegin()/.cend() for const iterators.
    cout << *iter << ",";

  cout << endl << "Using a for loop" << endl;
  for (std::string::size_type i = 0; i < str.size(); ++i)
    cout << str[i] << ",";

  cout << endl << "Using a C style null terminated array" << endl;
  for (const char* it = str.c_str(); *it; ++it) {
    cout << *it << ",";
  }
}

void main() {
  auto a = string("This is a test!");
  display(a);

  cout << std::endl <<  "[Press enter to exit]" << std::endl;
  std::cin.ignore();
}