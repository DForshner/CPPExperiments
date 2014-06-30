
// Parallel Task Pattern
// Performs distinct asynchronous operations that can run at the same time in parallel.
// AKA: Fork/Join and Master/Worker pattern.
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

void TaskA() {
  cout << "A";
  Work(15);
}

void TaskB() {
  cout << "B";
  Work(23);
}

void TaskC() {
  cout << "C";
  Work(20);
}

void Time(std::function<void()> f) {
  auto t1 = chrono::high_resolution_clock::now();
  f();
  auto t2 = chrono::high_resolution_clock::now();
  auto tt = (t2 - t1);
  cout << "Time: " << tt.count();
}

int main()
{
  vector<long> input(20);
  std::iota(input.begin(), input.end(), 17);

  cout << endl << "Start A & B & C in parallel and return when all tasks are finished." << endl;
  Concurrency::parallel_invoke(
    []() { TaskA(); },
    []() { TaskB(); },
    []() { TaskC(); }
  );

  cout << endl << "Start A & B & C in parallel and wait until all tasks are finished." << endl;
  Concurrency::task_group tg;
  tg.run([]() { TaskA(); });
  tg.run([]() { TaskB(); });
  tg.run([]() { TaskC(); });
  tg.wait(); // Block the current context until all tasks are complete.

  cout << endl << "Start A & B in parallel and wait until all tasks are finished." << endl;
  Concurrency::task_group tg2;
  tg2.run([]() { TaskA(); });
  tg2.run_and_wait([]() { TaskB(); }); // Attempt to start task b on the current thread.

  cout << endl << "Press enter to exit." << endl;
  cin.ignore();
  return 0;
}