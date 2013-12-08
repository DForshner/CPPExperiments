// Print out the contents of a 2D matrices 
// implemented using std::vector and std::array.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <vector>
#include <array>

using namespace std;

template <typename T>
void print(const vector<vector<T>> &a) {
  for (const auto &i : a) {
    for (const auto &j : i)
      cout << j;
  cout << endl;
  }
}

template <typename T, size_t ROW, size_t COL>
void print(const array<array<T, COL>, ROW> &a) {
  for (const auto &i : a) {
    for (const auto &j : i)
      cout << j;
  cout << endl;
  }
}

void main() {

  cout << endl << "Printing vector based matrix" << endl;
  auto vectorMatrix = vector<vector<int>> { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 8, 7, 2, 0 } };
  print(vectorMatrix);

  cout << endl << "Printing array based matrix" << endl;
  array<std::array<int, 4>, 3> arrayMatrix{ { { { 1, 2, 3, 1 } }, { { 4, 5, 6, 4 } }, { { 7, 8, 9, 7 } } } };
  print(arrayMatrix);

  cout << endl << "[Press enter to exit]" << endl;
  cin.ignore();
}