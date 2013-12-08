// Implement a function that takes a 2D matrix and prints it
// in a spiral order.  The matrix can have variable column lengths.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void print(const vector<vector<T>> &a) {

  // Determine matrix ranges. 
  int min_col = 0, max_col = 0, min_row = 0, max_row = a.size() - 1;
  for (const auto &i : a)
    max_col = (i.size() > max_col) ? i.size() - 1 : max_col;

  cout << "Matrix ranges row: [" << min_row << "-" << max_row << "]";
  cout << " column: [" << min_col << "-" << max_col << "]" << endl ;

  while (min_row <= max_row) {
    // Display top row from left to right
    for (auto col = min_col; col <= max_col; ++col)
      (col < a[min_row].size()) ? cout << a[min_row][col] << "," : cout << "*,";
    ++min_row;

    // Display right column from top to bottom
    for (auto row = min_row; row <= max_row; ++row)
      (max_col < a[row].size()) ? cout << a[row][max_col] << "," : cout << "*,";
    --max_col;

    // Display bottom row from right to left
    for (auto col = max_col; col >= min_col; --col)
      (col < a[max_row].size()) ? cout << a[max_row][col] << "," : cout << "*,";
    --max_row;

    // Display left column from bottom to top
    for (auto row = max_row; row >= min_row; --row)
      (min_col < a[max_row].size()) ? cout << a[row][min_col] << "," : cout << "*,";
    ++min_col;
  }
  cout << endl << endl;
}

void main()
{
  cout << "123" << endl;
  cout << "45" << endl;
  cout << "6789" << endl;
  cout << "321" << endl;
  auto matrix = vector<vector<int>> { { 1, 2, 3 }, { 4, 5 }, { 6, 7, 8, 9, }, { 3, 2, 1 } };
  print(matrix);

  cout << "123456" << endl;
  cout << "78" << endl;
  auto matrix2 = vector<vector<int>> { { 1, 2, 3, 4, 5, 6 }, { 7, 8 } };
  print(matrix2);

  cout << "[Press enter to exit]";
  cin.ignore();
}