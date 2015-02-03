#pragma once

#include <vector>
#include <string>

using namespace std;

//Knuth Shuffle
//Re-arranges a vector of strings in a random order.
//
//Notes:
//Assumes that RND gives a uniformly random number between 0 and 1.

class KnuthShuffle
{
public:  
  void Shuffle(std::vector<string>& v);
};