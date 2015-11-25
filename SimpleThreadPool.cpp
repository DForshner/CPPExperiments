// A simple thread pool to run a large number of tasks on 
// a fixed number of thread.
// 
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <atomic>
#include <thread>
#include <array>
#include <list>
#include <functional>
#include <list>
#include <condition_variable>
#include <mutex>

using namespace std;

namespace ThreadPool {

  constexpr int DEFAULT_NUM_THREADS = 4;

  template <unsigned NumThreads = DEFAULT_NUM_THREADS>
  class ThreadPool {

  public:
    ThreadPool()  {
      _numPendingTasks = 0;
      _isExiting= false;
      _isFinished = false;

      for (unsigned i = 0; i < NumThreads; ++i) {
        _threads[i] = move(thread([this, i] { this->RunTask(); }));
      }
    }

    ~ThreadPool() {
      JoinAll(); // Wait for all tasks to exit
    }

    inline size_t Size() const {
      return NumThreads;
    }

    inline size_t JobsRemaining() {
      lock_guard<mutex> guard(_taskQueueLock);
      return _taskQueue.size();
    }

    // Add a task to the queue
    void AddTask(function<void(void)> newTask) {
      lock_guard<mutex> guard(_taskQueueLock);
      _taskQueue.emplace_back(newTask);
      ++_numPendingTasks;

      // Notify any waiting threads that a new task is available.
      _taskAvailiableSignal.notify_one();
    }

    // Block until all tasks are complete
    // waitForAll - Wait for all pending tasks to complete before exiting.
    void JoinAll(bool waitForAll = true) {
      if (_isFinished) {
        return;
      }

      if (waitForAll) {
        WaitForAllTasksToComplete();
      }

      _isExiting = true;
      _taskAvailiableSignal.notify_all(); // Wake up all threads waiting for new tasks so they can exit.

      // Wait for threads to run out 
      for (auto& x : _threads) {
        if (x.joinable()) {
          x.join();
        }
      }

      _isFinished = true;
    }
        
    // Block until task queue is empty
    void WaitForAllTasksToComplete() {
      if (_numPendingTasks == 0) {
        return; // Nothing to do
      }

      unique_lock<mutex> lock(_emptySignalLock);
      // Wait for pool to be empty (all tasks have finished executing) before continuing
      _emptySignal.wait(lock, [this] {return this->_numPendingTasks == 0; });
      lock.unlock();
    }

  private:
    array<thread, NumThreads> _threads;
    list<function<void(void)>> _taskQueue;

    atomic_int _numPendingTasks;

    atomic_bool _isExiting;
    atomic_bool _isFinished;

    condition_variable _taskAvailiableSignal;
    condition_variable _emptySignal;

    mutex _emptySignalLock;
    mutex _taskQueueLock;

    void RunTask() {
      while (!_isExiting) {
        // Run the next task
        getNextTask()();
        --_numPendingTasks;

        // Notify waiting threads that a task has completed
        _emptySignal.notify_one();
      }
    }

    function<void(void)> getNextTask() {
      unique_lock<mutex> lock(_taskQueueLock);

      // Wait for a new task if queue is empty.
      _taskAvailiableSignal.wait(lock, [this] { return _taskQueue.size() || _isExiting; });

      if (!_isExiting.load()) {
        // Get a task from the queue
        auto task = _taskQueue.front();
        _taskQueue.pop_front();
        return task;
      } else {
        // Pool is exiting so return a null task 
        auto nullTask = [] {};
        ++_numPendingTasks;
        return nullTask;
      }
    }

  };

}

int main() {

  cout << "Create pool" << endl;
  ThreadPool::ThreadPool<6> pool;
  mutex streamLock;

  for (int i = 0; i < 250; ++i) {
    pool.AddTask([&streamLock, i]() { 
      auto numSec = i % 3 + 1;
      this_thread::sleep_for(chrono::seconds(numSec)); 

      lock_guard<mutex> guard(streamLock);
      cout << "Task: [" << i << "] Thread: [" << this_thread::get_id() << "] (" << numSec << " sec)" << endl;
    });
  }
  cout << "Tasks loaded" << endl;

  pool.JoinAll();
  cout << "Tasks complete" << endl;

  cout << endl << "[Press enter to exit]" << endl;
  cin.ignore();
  return 0;
}
