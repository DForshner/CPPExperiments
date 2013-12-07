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

namespace parallel_futures {

  typedef std::chrono::high_resolution_clock Clock;
  typedef std::chrono::duration<double, std::milli> Milliseconds;

  void spin(int ms){
    auto t1 = Clock::now();
    while (true){
      auto t2 = Clock::now();
      auto tt = (t2 - t1);
      Milliseconds res = Clock::duration(1);
      if (tt.count() * res.count() > ms)
          break;
    }
  }

  future<long> taskA(long i) {
    // Without specifying a launch policy it's up to the complier 
    // to chose to execute async or deferred (sync).
    return async([](long i) { i += 10; spin(10000); return i; }, i);
  }

  future<long> taskB(long i) {
    return async([](long i) { i *= 10; spin(15000); return i; }, i);
  }

  long taskC(long i) {
    spin(5000);
    return i * 100;
  }

  void run() {
    // Start tasks in parallel
    auto a = taskA(100);
    auto b = taskA(100);
    auto c = taskA(100);
    auto d = taskB(100);
    auto e = taskB(100);
    auto f = taskB(100);

    // Give main thread meaningful work to do instead of just blocking
    auto g = taskC(100);

    // gather parallel results.
    auto result = a.get() + b.get() + c.get() + d.get() + e.get() + f.get() + g;

    cout << "Answer is " << result << endl;
  }
}

int main()
{
  parallel_futures::run();

  cout << "[Press enter to exit]" << endl;
  cin.ignore();
  return 0;
}