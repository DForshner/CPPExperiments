#include <iostream>
#include <string>

using namespace std;

// Search array for existence of value using binary search.
// Each pass halves the searching space which gives the search
// O(log n) performance.
// Compiler: Microsoft Visual C++ Compiler Nov 2012 CTP (v120_CTP_Nov2012)

bool Exists(int key, int *a, const size_t size) {
    int low = 0;
    int high = size;

    std::cout << std::endl << "Searching for " << key << std::endl;

    // While there are still unexamined sections.
    while (low <= high)
    {
        std:cout << " | " << low << " <--> " << high << " | " << std::endl;        

        int median = (low + high) / 2;
       
        // Check if value at median is key
        if (a[median] == key) {
          std::cout << "FOUND at "<< median << std::endl;
          return true;
        }
      
        // Search lower half?
        if (a[median] > key)
          high = median -1;
        // Search upper half?
        else
          low = median + 1;
    }

    std::cout << "NOT FOUND" << std::endl;
    return false;
}

int main() {

  int values[] = {1,3,7,9,11,22,38,46,79,98,123,456,789,998};
  const size_t arraySize = sizeof(values) / sizeof(values[0]);
  auto exists = Exists(3, values, arraySize);

  Exists(38, values, arraySize);
  Exists(3, values, arraySize);
  Exists(4, values, arraySize);
  Exists(456, values, arraySize);
  Exists(998, values, arraySize);

  return 0;
}