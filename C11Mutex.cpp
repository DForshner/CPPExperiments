#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include <string>

// Compiler: Microsoft Visual C++ Compiler Nov 2012 CTP (v120_CTP_Nov2012)

struct SharedThing {
public:
    SharedThing(int startValue){
		counter = startValue;
	}

    void increase(const std::string& message){

		// When std::lock_guard<std::mutex> instance is created lock() is called on the mutex.  When destructed the lock is released.
		std::lock_guard<std::mutex> guard(lock);

		++counter;
		std::cout << message << " Counter:" << counter << std::endl;
    }

	int currentCount(){
		return counter;
	}
private:
	std::mutex lock;
    int counter;
};

void step1(SharedThing* thing){
	thing->increase("Step 1");
}

int main(){
	auto counter = new SharedThing(0);

	std::vector<std::thread> threads;

	for(int i = 0; i < 400; ++i){
		// Step 1
		threads.push_back(std::thread(step1, counter));

		// Step 2
		threads.push_back(std::thread([&counter](){
			counter->increase("Step 2");
		}
		));
    }

    for(auto& thread : threads){
		thread.join();
    }

	std::cout << "Final count: " << counter->currentCount();

    return 0;
}