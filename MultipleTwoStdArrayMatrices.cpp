// Multiply two std::Array based matrices together using templates.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <array>
#include <string>

using namespace std;

template <typename T, size_t ROW, size_t COL>
void display(array<array<T, COL>, ROW> matrix) {
  for (const auto &i : matrix) {
    for (const auto &j : i) {
      cout << ((j < 10) ? to_string(j) + " " : to_string(j));
    }
    cout << endl;
  }
}

template <typename T, size_t DIM1, size_t DIM2>
array<array<T,DIM2>,DIM2> multiply(array<array<T, DIM1>, DIM2> matrixA, array<array<T, DIM2>, DIM1> matrixB)
{
  array<array<T, DIM2>, DIM2> matrixC;
  auto size = matrixC.size();

  // Calculate each element in the new array
  for (auto i = 0; i < size; ++i) {
    for (auto j = 0; j < size;  ++j) {
      // Calculate current element
      matrixC[i][j] = 0;
      cout << "[" << i << "][" << j << "] = ";
      for (auto k = 0; k < (int)DIM1; ++k) {
        cout << matrixA[i][k] << " * " << matrixB[k][j] << ((k != matrixB.size() - 1) ? " + " : "");
        matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
      }
      cout << endl;
    }
  }

  return matrixC;
}

int main()
{
  array<array<int, 3>, 2> matrixA { {
    { { 1, 0, -2 } },
    { { 0, 3, -1 } },
  } };
  cout << endl << "Matrix A" << endl;
  display(matrixA);

  array<array<int, 2>, 3> matrixB{ {
    { { 0, 3 } },
    { { -2, -1 } },
    { { 0, 4 } },
  } };
  cout << endl << "Matrix B" << endl;
  display(matrixB);

  cout << endl << "Matrix C" << endl;
  auto matrixC = multiply(matrixA, matrixB);
  display(matrixC);

  cout << endl << "Matrix D" << endl;
  auto matrixD = multiply(matrixB, matrixA);
  display(matrixD);

  cout << "[Press enter to exit]" << endl;
  cin.ignore();
  return 0;
}