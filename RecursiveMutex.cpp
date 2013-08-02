#include <thread>
#include <iostream>
#include <mutex>
#include <string>

// Compiler: Microsoft Visual C++ Compiler Nov 2012 CTP (v120_CTP_Nov2012)

using namespace std;

std::timed_mutex timeLock;

void test(const std::string& threadName){
    std::chrono::milliseconds timeout(100);

    for(int i = 0; i < 10; ++i){

		// Give up trying to acquire the lock after a period of time.
        if(timeLock.try_lock_for(timeout)){
            std::cout << threadName << " - locked mutex." << std::endl;

			std::chrono::milliseconds sleepDuration(500);
			std::this_thread::sleep_for(sleepDuration);

            timeLock.unlock();
        } else {
            std::cout << threadName << " - failed to lock mutex." << std::endl;

            std::chrono::milliseconds sleepDuration(250);
            std::this_thread::sleep_for(sleepDuration);
        }
    }
}

int main(){
    std::thread t1(test, "Thread A");
    std::thread t2(test, "Thread B");

    t1.join();
    t2.join();

    return 0;
}