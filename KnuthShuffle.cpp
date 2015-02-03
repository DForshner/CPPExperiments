#include <algorithm>    // std::for_each
#include <vector>       // std::vector
#include <ctime>
#include "KnuthShuffle.h"

using namespace std;

void KnuthShuffle::Shuffle(std::vector<string>& list)
{
  srand(time(0)); // Reset the random number generator with the system clock.

  for (int i = 0; i < list.size(); i++)
  {
    double rnd_number = rand() / double(RAND_MAX); // return a uniform number in [0,1].

    // get a random index from the un-shuffled remainder of the list.
    int r = i + (int) (rnd_number * (list.size() - i));

    // swap the current index with the randomly selected 
    // point from the un-shuffled section of the list.
    string swap = list.at(r);
    list.at(r) = list.at(i);
    list.at(i) = swap;
  }
}