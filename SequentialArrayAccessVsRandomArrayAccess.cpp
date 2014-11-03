
#include <iostream>
#include <vector>
#include <chrono>
#include <memory>
#include <random> 
#include <set>
#include <cassert>
#include <algorithm>

// Naive benchmark that accesses array elements sequentially,
// sequentially with a step the size of the cache line, and 
// randomly.
// Complier: Visual Studio 2013 (v120)

using namespace std;

const static int SIZE = 10000000;
const static int ASSUMED_CACHE_LINE_SIZE = 64;
const static int STEP = ASSUMED_CACHE_LINE_SIZE / sizeof(char);
const static int LARGE_SIZE = SIZE * STEP;

void SumAllElements(const vector<int> &readOrder) {
  assert(readOrder.size() == SIZE);

  auto data = std::unique_ptr<char[]>(new char[SIZE]);
  std::fill_n(data.get(), SIZE, '3');

  std::chrono::high_resolution_clock clock;
  auto start = clock.now();

  // Sum every contiguous element
  unsigned sum = 0;
  for (const auto &i : readOrder) {
    sum += data[i];
  }

  auto end = clock.now();
  auto span = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  std::cout << "Final Sum: " << sum << " Time: " << span.count() << std::endl;
}

std::unique_ptr<vector<int>> CreateSequentialReadOrder() {
  auto order = unique_ptr<vector<int>>(new vector<int>());
  order->resize(SIZE);

  auto current = 0;
  std::generate(order->begin(), order->end(), [&current]() { return current++; });

  return order;
}

// Takes sum of SIZE 8 byte elements sequentially.
// This should allow to be loaded per summed element (assuming 64 byte cache line)
void SumEveryElementSequentially()
{
  auto order = CreateSequentialReadOrder();

  cout << endl << "- Sum every element contiguously -" << endl;

  SumAllElements(*order.get());
}

// Takes sum of SIZE elements sequentially in steps. 
// This should force one cache line to be loaded per summed element (assuming 64 byte cache line)
void SumEveryElementSequentiallyInSteps()
{
  cout << endl << "- Sum every element contiguously in steps -" << endl;

  auto data = std::unique_ptr<char[]>(new char[LARGE_SIZE]);
  std::fill_n(data.get(), LARGE_SIZE, '3');

  auto order = unique_ptr<vector<int>>(new vector<int>());
  order->resize(SIZE);

  auto current = -STEP; // Make first element zero
  std::generate(order->begin(), order->end(), [&current]() { return current += STEP; });
 
  std::chrono::high_resolution_clock clock;
  auto start = clock.now();

  // Sum every step element 
  unsigned sum = 0;
  for (const auto &i : *order) {
    sum += data[i];
  }

  auto end = clock.now();
  auto span = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  std::cout << "Final Sum: " << sum << " Time: " << span.count() << std::endl;
}

std::unique_ptr<vector<int>> CreateRandomReadOrder() {
  auto order = unique_ptr<vector<int>>(new vector<int>());
  order->resize(SIZE);

  auto current = 0;
  std::generate(order->begin(), order->end(), [&current]() { return current++; });

  std::shuffle(order->begin(), order->end(), random_device());

  return order;
}

void SumEveryElementRandomOrder()
{
  auto order = CreateRandomReadOrder();

  cout << endl << "- Sum every element randomly -" << endl;

  SumAllElements(*order.get());
}

int main()
{
  cout << "SIZE " << SIZE << endl;
  cout << "Char size " << sizeof(char) << " bytes." << endl;
  cout << "Assumed cache line size " << ASSUMED_CACHE_LINE_SIZE << endl;
  cout << "Step is " << STEP << endl;
  cout << "LARGE_SIZE is " << LARGE_SIZE << endl;

  SumEveryElementSequentially();
  SumEveryElementSequentiallyInSteps();
  SumEveryElementRandomOrder();

  cout << endl << "[Press enter to exit]" << endl;
  cin.ignore();
  return 0;
}