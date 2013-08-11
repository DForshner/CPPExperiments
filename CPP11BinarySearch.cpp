#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// C++11 STL implementations of binary search.
//
// binary_search - O(log(n)) for random access data.
// lower_bounds - O(log(n)) for random access data.
// upper_bounds - O(log(n)) for random access data. 
// equal_range - O(2 log(n)) random access data.
//
// Compiler: Microsoft Visual C++ Compiler Nov 2012 CTP (v120_CTP_Nov2012)

int main() {

  // Create vector of test values
  int const vals[] = {1,3,7,9,11,22,38,46,46,46,79,98,123,456,789,998};
  std::vector<int> values (vals, vals + sizeof (vals) / sizeof (vals[0]) );

  // Binary search using standard std::sort
  if (std::binary_search (values.begin(), values.end(), 3))
    std::cout << "FOUND 3" << std::endl;

  // Binary search using custom ordering comparison
  if (std::binary_search (values.begin(), values.end(), 789, [](int i, int j) { return (i<j); }))
    std::cout << "FOUND 789" << std::endl;

  // Get upper and lower bounds
  auto lowerBound = std::lower_bound(values.begin(), values.end(), 46);
  auto upperBound = std::upper_bound(values.begin(), values.end(), 46);

  std::cout << "Lower bound " << lowerBound - values.begin() << std::endl;
  std::cout << "Upper bound " << upperBound - values.begin() << std::endl;

  // Get equal range
  auto bounds = std::equal_range(values.begin(), values.end(), 46);
  std::cout << "Bounds " << bounds.first - values.begin() << " <--> " <<
    bounds.second - values.begin() << std::endl;

  return 0;
}