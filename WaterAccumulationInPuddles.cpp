// The heights of walls are represented in an array.
// If it rains how much water will accumulate in the puddles between walls?"
//
// Single pass O(n) implementation based on 
// http://qandwhat.apps.runkite.com/i-failed-a-twitter-interview/ 
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <vector>

using namespace std;

unsigned make_it_rain(const vector<int>& terrain) {
  unsigned left_max = 0, right_max = 0, left = 0, volume = 0;
  unsigned right = terrain.size() - 1;

  while (left < right) {
      if (terrain[left] > left_max) {
        left_max = terrain[left];
      }

      if (terrain[right] > right_max) {
        right_max = terrain[right];
      }

      if (left_max >= right_max)
        volume += right_max - terrain[right--];
      else
        volume += left_max - terrain[left++];
    }

  return volume;
}

void main() {

  auto terrain1 = vector<int> { { 2, 5, 1, 2, 3, 4, 7, 7, 6 } };
  cout << "Rain for terrain 1: " << make_it_rain(terrain1) << endl;

  auto terrain2 = vector<int> { { 2, 1, 3, 1, 5, 1, 1, 2, 3 } };
  cout << "Rain for terrain 2: " << make_it_rain(terrain2) << endl;

  cout << endl << "[Press enter to exit]";
  cin.ignore();
}