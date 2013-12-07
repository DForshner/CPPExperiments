// Split a string using a delimiter.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, elems);
  return elems;
}

void display(vector<std::string>* vec)
{
  cout << endl << "Result: " << endl;
  for (const auto &value: *vec) // access by reference to avoid copying
    cout << value << endl;
  cout << endl;
}

void main() {

  auto test = "This,is,a,test,!";
  auto result = split(test, ',');
  display(&result);

  auto test2 = "This is another test!";
  auto result2 = split(test2, ' ');
  display(&result2);

  cout << "[Press enter to exit]";
  cin.ignore();
}