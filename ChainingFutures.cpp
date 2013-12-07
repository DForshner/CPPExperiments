// Example of processing multiple task chains in parallel using C++ 11 async()
//
// Complier: Visual Studio 2013 (v120)

#include "stdafx.h"
#include <future>
#include <iostream>
#include <functional>
#include <thread>
#include <chrono>

using namespace std;

namespace chaining_futures {

  #define N_TASKS 64
  typedef std::chrono::high_resolution_clock Clock;
  typedef std::chrono::duration<double, std::milli> Milliseconds;

  void spin_for_second(){
    auto t1 = Clock::now();
    while (true){
      auto t2 = Clock::now();
      auto tt = (t2 - t1);
      Milliseconds res = Clock::duration(1);
      if (tt.count() * res.count()>1000)
          break;
    }
  }

  future<long> taskC(long i) {
    // Without specifying a launch policy it's up to the complier 
    // to chose to execute async or deferred (sync).
    return async([](long i) { i -= 3; spin_for_second(); return i; }, i);
  }

  future<long> taskB(long i) {
    // .get() blocks until taskC is complete.
    return async([](long i) { i *= 2; return taskC(i).get(); }, i);
  }

  future<long> taskA(long i) {
    // .get() blocks until taskB is complete.
    return async([](long i) { ++i; return taskB(i).get(); }, i);
  }

  void run() {
    future<long> tasks[N_TASKS];

    for (long i = 0; i < N_TASKS; ++i) {
      tasks[i] = taskA(i);
    }

    // Display results of tasks that ran.
    // .get() blocks (releasing main thread) until results are ready.
    for (long i = 0; i < N_TASKS; ++i){
      cout << "Answer for task chain " << i << " is " << tasks[i].get() << endl;
    }
  }

  void measure(long count, std::function<void()> toRun){
    for (; count > 0 ; --count) {
      // Run task
      auto t1 = Clock::now();
      toRun();
      auto t2 = Clock::now();

      // Display how long it took to run all tasks.
      auto tt = (t2 - t1);
      Milliseconds res = Clock::duration(1);
      std::cout << "Total: " << tt.count() * res.count() << '\n';
    }
  }
}

int main()
{
  chaining_futures::measure(1, chaining_futures::run);

  cout << "[Press enter to exit]" << endl;
  cin.ignore();
  return 0;
}