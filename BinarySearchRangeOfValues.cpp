#include <iostream>
#include <string>
#include <functional>

using namespace std;

// Search a range of values for nearest value that satisfies a predicate.
// Each pass halves the search space which gives the search for O(log n) performance.
//
// Compiler: Microsoft Visual C++ Compiler Nov 2012 CTP (v120_CTP_Nov2012)

// Finds the first value for which the predicate is true
int BinarySearch(int upper, int lower, std::function<bool (int)> predicate)
{
    while (lower < upper) {
      // Because Division truncates we are not using (low + high) / 2.
      // It would cause values where (upper-lower) is negative to round 
      // up and where (upper - lower) is positive to round down.
      auto median = lower + (upper - lower) / 2;

      if (predicate(median))
        // Discard the second half of the solution space because all values
        // after this will be true for the predicate.  We must keep the median
        // because it could be the first element for which the predicate is true.
        upper = median;
      else
        // Discard the first half of the search space because the median and
        // everything belong is will be false for the predicate.
        lower = median + 1;
    }

    // Check if there was no match
    if (!predicate(lower))
      return 0; // The predicate was false for all values

    return lower; // The greatest value for which the predicate was false.
}

int BinarySearchFindGreatestThatFailed(int lower, int upper, std::function<bool (int)> predicate)
{
    while (lower < upper) {
      // Add +1 so rounds up instead of down to prevent the median from
      // getting stuck always selecting the first value of a two element array.
      auto median = lower + (upper - lower + 1) / 2;

      if (predicate(median))
        upper = median - 1;
      else
        lower = median;
    }

    // Check if there was no match
    if (predicate(lower))
      return 0; // The predicate was true for all values

    return lower; // The greatest value for which the predicate was false.
}

#define RUNS 100000

// Iteratively searches for number closest to the first number
// that would satisfy the predicate.
float BinarySearchFloat(float lower, float upper, std::function<bool (float)> predicate)
{
    for (auto i = RUNS; i > 0; --i) {
      auto median = lower + (upper - lower) / 2;

      if (predicate(median))
        upper = median;
      else
        lower = median;
    }
    
    // Return the lowest value for which the predicate was true
    return lower;
}

int main() {

  auto result = BinarySearch(1, 2, [](int i) { return (i > 44); });
  std::cout << "First value that is greater than 44 is " << result << std::endl;
  std::cout << "The zero indicates no value was found" << std::endl << std::endl;

  auto result2 = BinarySearch(1, 100, [](int i) { return (i > 44); });
  std::cout << "First value that is greater than 44 is " << result2 << std::endl;

  auto result3 = BinarySearchFindGreatestThatFailed(1, 100, [](int i) { return (i > 44); });
  std::cout << "Last value that was not greater than 44 is " << result3 << std::endl;

  auto result4 = BinarySearchFloat(1.0, 10000.0, [](float i) { return (i > 2000.55555555); });
  std::cout << std::endl << "First value that satisfies predicate is is " << result4 << std::endl;

  return 0;
}