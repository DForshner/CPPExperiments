// Consider a stick of length 1. Pick two points uniformly at random on the stick, 
// and break the stick at those points. What is the probability that the 
// three segments obtained in this way form a triangle?
//
// See: http://www.cut-the-knot.org/Curriculum/Probability/TriProbCartesian.shtml
//
// Compiler: Microsoft Visual C++ Compiler Nov 2012 CTP (v120_CTP_Nov2012)

#include <iostream>
#include <chrono>
#include <random>

const unsigned int NUM_CALCULATIONS = 10000000;

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds milliseconds;

int main()
{
	float pointA, pointB, temp;
	unsigned int canMakeTriangle = 0;

	std::default_random_engine generator((unsigned int)time(0));
	std::uniform_real_distribution<float> distribution(0.0, 1.0);

	std::cout << "Starting brute force probability estimate." << std::endl;

	Clock::time_point t0 = Clock::now();

	for (auto i = 0; i <= NUM_CALCULATIONS ; ++i)
	{
		pointA = distribution(generator);
		pointB = distribution(generator);

		// |--A---B--|
		if (abs(pointA - pointB) > 0.5)
			continue;

		// Swap variables.
		if (pointA > pointB)
		{
			temp = pointA;
			pointA = pointB;
			pointB = temp;
		}

		// |--A--B---|       |---A--B--|
		if (pointB < 0.5 || pointA > 0.5)
			continue;

		++canMakeTriangle;
	}

	Clock::time_point t1 = Clock::now();

	auto answer = (float) canMakeTriangle / (float) NUM_CALCULATIONS;
	std::cout << std::endl << "Probability that triangle can be made is: " << canMakeTriangle << " / " << NUM_CALCULATIONS << " = " << answer << std::endl;

	milliseconds ms = std::chrono::duration_cast<milliseconds>(t1 - t0);
	auto throughput = NUM_CALCULATIONS / ms.count();
	std::cout << std::endl << "Throughput was: " << throughput << " Calc. / ms." << std::endl;

	std::cout << "Press ENTER to exit." << std::endl;
	std::cin.get();

	return 0;
}