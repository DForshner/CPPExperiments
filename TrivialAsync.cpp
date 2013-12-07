// Example of processing multiple tasks concurrently using C++ 11 async()
//
// Complier: Visual Studio 2013 (v120)

#include "stdafx.h"
#include <future>
#include <iostream>
#include <functional>
#include <thread>
#include <chrono>
#include <string>

using namespace std;

namespace trivial_async {

  #define N_TASKS 64
  typedef std::chrono::high_resolution_clock Clock;
  typedef std::chrono::duration<double, std::milli> Milliseconds;

  void spin_for_second(){
    auto t1 = Clock::now();
    while (true){
      auto t2 = Clock::now();
      auto tt = (t2 - t1);
      Milliseconds res = Clock::duration(1);
      if (tt.count() * res.count() > 1000)
        break;
    }
  }

  std::future<string> simple_task(long i) {
    // Without specifying a launch policy it's up to the complier 
    // to chose to execute async or deferred (sync).
    return async([](long i) { spin_for_second(); return "Work[" + to_string(i) + "]"; }, i);
  }

  void run() {
    // Create array of running tasks.
    future<string> tasks[N_TASKS];
    for (auto i = 0; i < N_TASKS; ++i) {
      tasks[i] = simple_task(i);
    };

    // Display results of tasks when they are ready.
    // .get() blocks (releasing main thread) until results are ready.
    for (auto i = 0; i < N_TASKS; ++i){
      cout << "Result for simple task " << i << ": " << tasks[i].get() << endl;
    }
  }
}

void main() {
  trivial_async::run();

  cout << endl << "[Press enter to exit]" << endl;
  cin.ignore();
}