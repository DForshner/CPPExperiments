
// Parallel For Loop Pattern
// Performs the same independent operation for each element in a collection or a fixed number of iterations.
//
// Complied: Visual Studio 2013. 
// Uses Microsoft's Parallel Patterns Library

#include <iostream>
#include <ppl.h>
#include <vector>
#include <numeric>
#include <chrono>

using namespace ::std;

// Simulate a large workload. Consumes a lot of stack.
long Work(const long &i) {
  if (i == 0 || i == 1)
    return i;
  return Work(i - 1) + Work(i - 2);;
}

void Display(const vector<long>& v) {
  cout << endl;
  for (auto const &i : v) {
    cout << i << ",";
  }
  cout << endl;
}

void Time(std::function<void()> f) {
  auto t1 = chrono::high_resolution_clock::now();
  f();
  auto t2 = chrono::high_resolution_clock::now();
  auto tt = (t2 - t1);
  cout << "Time: " << tt.count();
}

vector<long> SequentialForLoop(const vector<long> &input) {
  vector<long> results(input.size());
  for (auto i = 0; i < input.size(); i++) {
    results[i] = Work(input[i]);
  }
  return results;
}

vector<long> ParallelForLoop(const vector<long> &input) {
  vector<long> results(input.size());
  Concurrency::parallel_for(0u, input.size(), [&results, &input](size_t i) {
    results[i] = Work(input[i]); // Each write to result[i] will be independent
  });
  return results;
}

vector<long> SequentialForEachLoop(const vector<long> &input) {
  vector<long> results;
  for_each(input.cbegin(), input.cend(), [&results](size_t i) {
    results.push_back(Work(i));
  });

  // Equivalent to
  //for (auto &i : input) {
  //  results.push_back(Work(i));
  //}

  return results;
}

vector<long> ParallelForEachLoop(const vector<long> &input) {
  Concurrency::combinable<vector<long>>results;
  Concurrency::parallel_for_each(input.cbegin(), input.cend(), [&results](long i) {
    results.local().push_back(Work(i));
  });
  // Return combined results
  return results.combine([](vector<long> v1, const vector<long> v2) { 
    v1.insert(v1.end(), v2.cbegin(), v2.cend());
    return v1;
  });
}

int main()
{
  vector<long> input(20);
  std::iota(input.begin(), input.end(), 17);

  Time([&input]() { Display(SequentialForLoop(input)); });
  Time([&input]() { Display(ParallelForLoop(input)); });
  Time([&input]() { Display(SequentialForEachLoop(input)); });
  Time([&input]() { Display(ParallelForEachLoop(input)); });

  cout << endl << "Press enter to exit." << endl;
  cin.ignore();
  return 0;
}