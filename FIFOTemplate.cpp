#include <thread>
#include <iostream>
#include <mutex>
#include <string>
#include <future>

// Compiler: Microsoft Visual C++ Compiler Nov 2012 CTP (v120_CTP_Nov2012)

using namespace std;

template <typename T>
struct FIFOQueue {

public:
    FIFOQueue(T capacity = T()) : maxCapacity(capacity), front(0), rear(0), currentCount(0) {
        queue = new T[capacity];
    }

    ~FIFOQueue(){
        delete[] queue;
    }

    void push(T data){	
		// A condition variable requires any thread that wants to wait on it to acquire a std::unique_lock first.
		std::unique_lock<std::mutex> uniqueLock(lock);

		// Releases mutex and suspend until the condition variable is notified.  When notified awaken the thread and re-acquire the lock.
		// The predicate section protects against a spurious wake-up by looping until the condition is true before proceeding.
		notifyNotFull.wait(uniqueLock, [&](){return currentCount != maxCapacity; });

		queue[rear] = data;
		rear = (rear + 1) % maxCapacity;
		++currentCount;

		notifyNotEmpty.notify_one();
    }

    T pop(){
        std::unique_lock<std::mutex> uniqueLock(lock);

        notifyNotEmpty.wait(uniqueLock, [&](){return currentCount != 0; });

		int result = queue[front];
		front = (front + 1) % maxCapacity;
		--currentCount;
		notifyNotFull.notify_one();	

        return result;
    }

private:
    int* queue;
    int maxCapacity;

    int front;
    int rear;
    int currentCount;

    std::mutex lock;
    std::condition_variable notifyNotFull;
    std::condition_variable notifyNotEmpty;
};

void consumer(const std::string& name, FIFOQueue<int>& queue){
    for(int i = 0; i < 10; ++i){
        auto value = queue.pop();
        std::cout << name << " - Popped " << value << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

void producer(const std::string& name, FIFOQueue<int>& queue){
    for(int i = 0; i < 15; ++i){
        queue.push(i);
        std::cout << name << " - Pushed " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main(){
    FIFOQueue<int> queue(200);

	std::vector<std::thread> threads;

	threads.push_back(std::thread(consumer, "Consumer A", std::ref(queue))); // Use std::ref to pass by reference
	threads.push_back(std::thread(consumer, "Consumer B", std::ref(queue)));
	threads.push_back(std::thread(consumer, "Consumer C", std::ref(queue)));
	threads.push_back(std::thread(producer, "Producer A", std::ref(queue)));
	threads.push_back(std::thread(producer, "Producer B", std::ref(queue)));

	for(auto& thread : threads){
		thread.join();
    }

    return 0;
}