// Design an algorithm that tracks buildings that have a view of the sunset.
// Heights are provided for buildings from east to west as a string.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

struct Building {
  unsigned height;
  unsigned index;
  Building(unsigned _height, unsigned _index) : height(_height), index(_index) {}
};

vector<Building> buildings_with_view_east_to_west(istringstream &ss) {
  vector<Building> buildings;
  unsigned height = 0, index = 0;

  while (ss >> height) {
    // Push the first building
    if (buildings.empty()) {
      buildings.push_back(Building(height, index++));
      continue;
    }

    // Remove all the shorter buildings because their views will be blocked.
    while (!buildings.empty() && height >= buildings.back().height)
      buildings.pop_back();

    buildings.push_back(Building(height, index++));
  }

  return buildings;
}

vector<Building> buildings_with_view_west_to_east(istringstream &ss) {
  vector<Building> buildings;
  unsigned height = 0;
  int index = 0;

  while (ss >> height) {
    // Push the first building
    if (buildings.empty()) {
      buildings.push_back(Building(height, index++));
      continue;
    }

    // Only add to stack if building is greater than top
    if (!buildings.empty() && height > buildings.back().height)
        buildings.push_back(Building(height, index++));
  }

  return buildings;
}

void main() {
  istringstream ss;

  // East to West
  ss.str("32 1000 22 33 100 300 33 300 300 200 100 75 10 20 30 10");
  auto buildings_east_west = buildings_with_view_east_to_west(ss);

  cout << endl << "Buildings with a view of the sunset from East to West" << endl;
  for (const auto &building : buildings_east_west)
    cout << "Building: [" << building.index << "] with height " << building.height << endl;

  // West to East 
  ss.clear();
  ss.str("10 30 20 10 75 100 200 300 300 33 300 100 33 22 1000 32");
  auto buildings_west_east = buildings_with_view_west_to_east(ss);

  cout << endl << "Buildings with a view of the sunset from West to East" << endl;
  for (const auto &building : buildings_west_east)
    cout << "Building: [" << building.index << "] with height " << building.height << endl;

  cout << endl << "[Press enter to exit]";
  cin.ignore();
}