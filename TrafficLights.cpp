#include <iostream>
#include <future>

// Compiler: Microsoft Visual C++ Compiler Nov 2012 CTP (v120_CTP_Nov2012)

class trafficLight {

public:
  trafficLight () {}

  void start() {
    redComplete.notify_one();
  }

  void turnGreen () {
    std::unique_lock <std::mutex> lock (lock);
	  redComplete.wait(lock);
	  std::cout << "Green!" << std::endl;
    waitDelay();
	  greenComplete.notify_one();
  }

  void turnYellow () {
    std::unique_lock <std::mutex> lock (lock);
	  greenComplete.wait(lock);
	  std::cout << "Yellow!" << std::endl;
    waitDelay();
	  yellowComplete.notify_one();
  }

  void turnRed () {
    std::unique_lock <std::mutex> lock (lock);
	  yellowComplete.wait(lock);
	  std::cout << "Red!" << std::endl;
    waitDelay();
	  redComplete.notify_one();
  }

private:
  std::mutex lock;
  std::condition_variable greenComplete;
  std::condition_variable yellowComplete;
  std::condition_variable redComplete;

  void waitDelay () {
    std::chrono::milliseconds sleepDuration(1000);
    std::this_thread::sleep_for(sleepDuration);
  }
};

void red (trafficLight* light)
{
	while(true) {
    light->turnRed();
	}
}

void yellow (trafficLight* light)
{
	while(true) {
    light->turnYellow();
	}
}

void green (trafficLight* light)
{
	while(true) {
    light->turnGreen();
	}
}

int main () 
{
	std::cout << "Start!" << std::endl;
  
  auto light = new trafficLight();

  auto greenThread = std::thread(green, light);
  auto yellowThread = std::thread(yellow, light);
  auto redThread = std::thread(red, light);

  light->start();

  // Barrier synchronization to join all the threads back together.
  greenThread.join ();
  yellowThread.join ();
  redThread.join ();

  std::cout << "Done!" << std::endl;

  return 0;
}
