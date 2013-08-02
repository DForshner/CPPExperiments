// Insertion sorts
//
// Compiler: Microsoft Visual C++ Compiler Nov 2012 CTP (v120_CTP_Nov2012)

#include <iostream>
#include <chrono>
#include <random>
#include <vector>

const unsigned int NUM_ELEMENTS = 1000;

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds milliseconds;

std::vector<unsigned int> generateRandomVector(int size)
{
	std::default_random_engine generator((unsigned int)time(0));
  std::uniform_int_distribution<unsigned int> distribution(0, UINT_MAX);

	std::vector<unsigned int> vectorToSort;
  
  vectorToSort.reserve(size); // Pre-allocate memory but do not initialize variables.

  for (int x = 0; x < size; x++)
    vectorToSort.push_back(distribution(generator));
   
	return vectorToSort;
}

void insertionSort (std::vector<unsigned int>& vectorToSort) 
{
  int size = vectorToSort.size();
	int current, inspection, temp;

	for (current = 1; current < size; current++)
	{
		inspection = current;
		
    temp = vectorToSort[current];

		while (inspection > 0 && temp < vectorToSort[inspection - 1])
		{
			vectorToSort[inspection]=vectorToSort[inspection - 1];
			--inspection;
		}

		vectorToSort[inspection] = temp;
  }
}

int main()
{
	std::cout << "Starting - Insertion sort." << std::endl;

	auto vectorToSort = generateRandomVector(NUM_ELEMENTS);

	Clock::time_point t0 = Clock::now();

	insertionSort(vectorToSort);

	Clock::time_point t1 = Clock::now();
	milliseconds ms = std::chrono::duration_cast<milliseconds>(t1 - t0);
	
  auto throughput = NUM_ELEMENTS / ms.count();
  std::cout << std::endl << "Throughput was: " << throughput << " Sorts / ms." << std::endl;

	std::cout << "Complete - Press ENTER to exit." << std::endl;
	std::cin.get();

	return 0;
}