// False sharing (cache line ping-ponging)
//
// When threads use objects that are close enough in memory to fall on the same cache line, the cache system
// will protect the entire cache line with a hardware write lock that only allows one thread (core) can hold at a time.
// The thread holding the lock so it can update will block other threads trying to use the objects that
// are nearby in memory (sits in the same cache line).
//
// One scenario might be a reader thread accessing read only data that gets blocked by a writer thread updating
// a different but nearby memory location.
//
// Based on: http://www.drdobbs.com/parallel/eliminate-false-sharing/217500206?pgno=1
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <array>
#include <chrono>

using namespace std;

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::duration<double, std::milli> Milliseconds;

const int DIM = 5000;

// Wait all parallel threads to complete.
void join_all(std::vector<std::thread>& v)
{
  std::for_each(v.begin(), v.end(), [](std::thread& t) { t.join(); });
}

template <typename T, size_t ROW, size_t COL>
array<array<T, COL>, ROW>* create() {
  auto matrix = new array<array<T,COL>,ROW>();
  T count = 0;
  for (auto &i : *matrix) {
    for (auto &j : i)
      j = count++;
  }
  return matrix;
}

void flawed(int num_threads, array<array<int, DIM>, DIM>* matrix) {

  // Each worker is incrementing its own distinct counter, but the counter values are adjacent 
  // in the result array. To increment its counter, a worker must have exclusive ownership of 
  // the cache line containing the counter, which means that the other workers trying to update 
  // their counters elsewhere in that same cache line must stall and wait until they can in turn
  // get exclusive access to the line containing their chunk of result.

  // This can also happen with two objects or fields that are frequently accessed(either read or written) by different threads, 
  // at least one of the threads is doing writes, and the objects are so close in memory that they're on the same cache line because they are:
  int result[8];

  std::vector<std::thread> v(num_threads);
  for (unsigned t = 0; t < v.size(); ++t)
  {
    v[t] = std::thread([&, t] {
      result[t] = 0;
      // Each of P parallel workers processes 1/P-th of the data.
      int chunkSize = DIM / num_threads + 1;
      int myStart = t * chunkSize;
      int myEnd = min(myStart + chunkSize, DIM);
      for (int i = myStart; i < myEnd; ++i) {
        for (int j = 0; j < DIM; ++j) {
          if (matrix->at(i)[j] % 2 != 0)
            ++result[t];
          }
        }
    });
  }

  // Reduce
  join_all(v);
  auto odds = 0;
  for (int p = 0; p < num_threads; ++p) {
    odds += result[p];
  }
}

// The simplest way to fix the problem is simply to have each p-th worker increment its own local variable, 
// and only at the end write its final tally to result[p]. 
// we can reduce the number of writes to the cache line.For example, writer threads can write intermediate 
// results to a scratch variable most of the time, then update the variable in the popular cache line only occasionally as needed.
void fixed(int num_threads, array<array<int, DIM>, DIM>* matrix) {

  // the p-th worker records its partial count in result[p]
  int result[8];

  std::vector<std::thread> v(num_threads);
  for (unsigned t = 0; t < v.size(); ++t)
  {
    v[t] = std::thread([&, t] {
        unsigned local_count = 0;
        // Each of P parallel workers processes 1/P-th of the data.
        int chunkSize = DIM / num_threads + 1;
        int myStart = t * chunkSize;
        int myEnd = min(myStart + chunkSize, DIM);
        for (int i = myStart; i < myEnd; ++i) {
          for (int j = 0; j < DIM; ++j) {
            if (matrix->at(i)[j] % 2 != 0)
              local_count++;
          }
        }

        // Save results back to shared variable.
        result[t] = local_count;
    });
  }

  // Reduce
  join_all(v);
  auto odds = 0;
  for (int p = 0; p < num_threads; ++p) {
    odds += result[p];
  }
}

#define CACHE_LINE_SIZE 128 // Commonly a power of two from 16 to 512. 
#define CACHE_ALIGN __declspec(align(CACHE_LINE_SIZE))


// Ensure that no other object can precede your data in the same cache line by 
// aligning it o begin at the start of the cache line or adding sufficient padding 
// bytes before the object.
template <typename T>
struct CACHE_ALIGN aligned_result{
  T value;

  // Ensure that no other object can follow your data in the same cache line by 
  // adding sufficient padding bytes after the object to fill up the line.
  char pad[CACHE_LINE_SIZE > sizeof(T)
    ? CACHE_LINE_SIZE - sizeof(T)
    : 1];
};

void align_in_cache(int num_threads, array<array<int, DIM>, DIM>* matrix) {
  aligned_result<int> result[8];

  std::vector<std::thread> v(num_threads);
  for (unsigned t = 0; t < v.size(); ++t)
  {
    v[t] = std::thread([&, t] {
      result[t].value = 0;
      // Each of P parallel workers processes 1/P-th of the data.
      int chunkSize = DIM / num_threads + 1;
      int myStart = t * chunkSize;
      int myEnd = min(myStart + chunkSize, DIM);
      for (int i = myStart; i < myEnd; ++i) {
        for (int j = 0; j < DIM; ++j) {
          if (matrix->at(i)[j] % 2 != 0)
            ++result[t].value;
        }
      }
    });
  }

  // Reduce
  join_all(v);
  auto odds = 0;
  for (int p = 0; p < num_threads; ++p) {
    odds += result[p].value;
  }
}

int main() {

  auto matrix = create<int,DIM,DIM>();
  cout << endl << "Allocated " << sizeof(array<array<int,DIM>,DIM>) << " bytes" << endl;
  auto max_threads = std::thread::hardware_concurrency();

  cout << "Example 1 - Shared variables causing thread blocking." << endl;
  for (auto i = 1; i <= max_threads; ++i) {
    auto t1 = Clock::now();
    flawed(i, matrix);
    auto t2 = Clock::now();
    auto tt = (t2 - t1);
    Milliseconds res = Clock::duration(1);
    cout << "Time for " << i << " threads was " << tt.count() << endl;
  }

  cout << "Example 2 - Use local variables for frequent reading/writing." << endl;
  for (auto i = 1; i <= max_threads; ++i) {
    auto t1 = Clock::now();
    fixed(i, matrix);
    auto t2 = Clock::now();
    auto tt = (t2 - t1);
    Milliseconds res = Clock::duration(1);
    cout << "Time for " << i << " threads was " << tt.count() << endl;
  }

  cout << "Example 3 - Aligning shared variables in cache" << endl;
  for (auto i = 1; i <= max_threads; ++i) {
    auto t1 = Clock::now();
    align_in_cache(i, matrix);
    auto t2 = Clock::now();
    auto tt = (t2 - t1);
    Milliseconds res = Clock::duration(1);
    cout << "Time for " << i << " threads was " << tt.count() << endl;
  }

  cout << "[Press enter to exit]" << endl;
  cin.ignore();
  return 0;
}