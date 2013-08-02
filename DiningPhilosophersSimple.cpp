// A dining philosophers solution solved using the Resource Hierarchy solution. 
// Each philosopher is represented by a std::thread and attempts to access
// both the of the chopsticks (shared resource) to their left and right.
// 
// Compiler: Microsoft Visual C++ Compiler Nov 2012 CTP (v120_CTP_Nov2012)

#include <string>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <future>
#include <chrono>

using namespace std;

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds milliseconds;

#define MAXTIMESTOEAT 5

// The Monitor class is an implementation of the monitor object pattern.
// This implementation allows synchronized data of type T to be passed to hook methods 
// that do additional work during the critical sections.
template <class T>
class Monitor {

public:
	Monitor () : in_use_(false) { }

	// Main event loop that runs in a separate thread of control.
	virtual void Lock (T synchronized_data) 
	{
		std::unique_lock<std::mutex> lock(lock_);

		if (in_use_ == true) {
			not_in_use_.wait(lock, [&](){return in_use_ == false; });
		}

		in_use_ = true;

		SynchronizedAcquire(synchronized_data);
	}

	virtual void Unlock (T synchronized_data) 
	{
		std::unique_lock<std::mutex> lock(lock_);

		SynchronizedRelease(synchronized_data);

		in_use_ = false;

		// Notify a single thread that is waiting that this object is now free
		not_in_use_.notify_one();
	}

	// Virtual hook method to do work while the monitor object is being locked.
	virtual void SynchronizedAcquire (T synchronized_data) = 0 ;
	
	// Virtual hook to do work while the monitor object is being released.
	virtual void SynchronizedRelease (T synchronized_data) = 0 ;

private:
	std::mutex lock_;
	
	// Holds the state of whether this monitor object is in use or not.
	bool in_use_;
	
	// Signals to a waiting thread that this monitor object is not in use
	std::condition_variable not_in_use_;
};


// Represents a chopstick (shared resource).
class Chopstick : public Monitor<const std::string&> {

public:
	Chopstick(const int id) : Monitor(), chop_stick_id_(id) {}

	// Picks up this chop stick
	void PickUp(const std::string& message)
	{
		Lock(message);		
	}

	// Releases this chop stick
	void PutDown(const std::string& message)
	{
		Unlock(message);
	}

	int const chop_stick_id()
	{
		return chop_stick_id_;
	}

private:
	// Displays a message about the chopstick being picked up inside the monitor object critical section.
	virtual void SynchronizedAcquire(const std::string& message)
	{
		std::cout << message << std::endl;
	}

	// Displays a message about the chopstick being put down inside the monitor object critical section.
	virtual void SynchronizedRelease(const std::string& message)
	{ 
		std::cout << message << std::endl;
	}

	const int chop_stick_id_;
};

 // Represents a philosopher (worker).  A philosopher has a chopstick on their left 
 // and right and must successfully pick up both to eat (do work).
class Philosopher {

public:
	Philosopher(const int id, Chopstick* left_chopstick, Chopstick* right_chopstick) : philosopher_id_(id), times_eaten_(0)
	{
		// Sort the chopsticks into low and high resource ids.
		if (left_chopstick->chop_stick_id() < right_chopstick->chop_stick_id())
		{
			low_chopstick_ = left_chopstick;
			low_chopstick_side_ = "left";
			high_chopstick_ = right_chopstick;
			high_chopstick_side_ = "right";
		} else {
			low_chopstick_ = right_chopstick;
			low_chopstick_side_ = "left";
			high_chopstick_ = left_chopstick;
			high_chopstick_side_ = "right";
		}
	}

	int const philosopher_id()
	{
		return philosopher_id_;
	};

	void Eat()
	{
		while(times_eaten_ < MAXTIMESTOEAT)
		{
			low_chopstick_->PickUp("Philosopher " + std::to_string(philosopher_id_) + " picks up " + low_chopstick_side_ + " chopstick.");

			high_chopstick_->PickUp("Philosopher " + std::to_string(philosopher_id_) + " picks up " + high_chopstick_side_ + " chopstick.");

			std::cout << "Philosopher " + std::to_string(philosopher_id_) + " eats." << std::endl;

			times_eaten_++;

			high_chopstick_->PutDown("Philosopher " + std::to_string(philosopher_id_) + " puts down " + high_chopstick_side_ + " chopstick.");

			low_chopstick_->PutDown("Philosopher " + std::to_string(philosopher_id_) + " puts down " + low_chopstick_side_ + " chopstick.");
		}
	}

private:
	const int philosopher_id_;

	// Number of times this philosopher has eaten.
	int times_eaten_;
	Chopstick* low_chopstick_;
	Chopstick* high_chopstick_;

	// Stores which sides the low/high chopsticks are on for display purposes.
	std::string low_chopstick_side_;
	std::string high_chopstick_side_;
};

// Simple function to start philosophers eating.
void work(Philosopher* philosopher)
{
	philosopher->Eat();
}

int main(){

	Clock::time_point start_time = Clock::now();

	std::cout << "Dinner is starting!" << std::endl << std::endl;

	auto c1 = new Chopstick(1);
	auto c2 = new Chopstick(2);
	auto c3 = new Chopstick(3);
	auto c4 = new Chopstick(4);
	auto c5 = new Chopstick(5);

	std::vector<std::thread> threads;
	threads.push_back(std::thread(work, new Philosopher(1, c1, c2)));
	threads.push_back(std::thread(work, new Philosopher(2, c2, c3)));
	threads.push_back(std::thread(work, new Philosopher(3, c3, c4)));
	threads.push_back(std::thread(work, new Philosopher(4, c4, c5)));
	threads.push_back(std::thread(work, new Philosopher(5, c5, c1)));

	// Wait to finish eating
    for(auto& thread : threads){
		thread.join();
    }

	std::cout << "Dinner is over!" << std::endl << std::endl;

	Clock::time_point end_time = Clock::now();
	milliseconds ms = std::chrono::duration_cast<milliseconds>(end_time - start_time);
	std::cout << std::chrono::milliseconds(ms).count() << " ms" << std::endl;

    return 0;
}