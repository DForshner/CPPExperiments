// Displays the upper and lower triangle of a square matrix.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <array>
#include <string>

using namespace std;

int main()
{
  array<array<int, 5>, 5> matrix { {
    { { 1, 2, 3, 4, 5 } },
    { { 1, 2, 3, 4, 5 } },
    { { 1, 2, 3, 4, 5 } },
    { { 1, 2, 3, 4, 5 } },
    { { 1, 2, 3, 4, 5 } },
  } };

  cout << endl << "Matrix" << endl;
  for (const auto &i : matrix) {
    for (const auto &j : i) {
      cout << j;
    }
    cout << endl;
  }

  cout << endl << "Top Triangle" << endl;
  for (auto i = 0; i < matrix.size(); ++i) {
    for (auto j = 0; j < matrix[i].size(); ++j) {
      cout << ((i < j) ? to_string(matrix[i][j]) : string("X"));
    }
    cout << endl;
  }

  cout << endl << "Bottom Triangle" << endl;
  for (auto i = 0; i < matrix.size(); ++i) {
    for (auto j = 0; j < matrix[i].size(); ++j) {
      cout << ((i > j) ? to_string(matrix[i][j]) : string("X"));
    }
    cout << endl;
  }

  cout << "[Press enter to exit]" << endl;
  cin.ignore();
  return 0;
}