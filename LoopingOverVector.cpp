// Display a vector using ranged based loop,
// an iterator, and for_each.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>;
#include <vector>;
#include <functional>;
#include <algorithm>;

using namespace std;

void display_vector(const vector<int>& vec) {
  cout << endl << "C++11 Ranged based for loop" << endl;
  for (const auto &value: vec) // access by reference to avoid copying
    cout << value;

  cout << endl << "Using iterators" << endl;
  for (auto iter = vec.cbegin(); iter != vec.cend(); ++iter) // .cbegin()/.cend() for const iterators.
    cout << *iter;

  cout << endl << "Using <algorithim> for_each" << endl;
  auto f = function<void(int)>([](const int value) { cout << value; });
  std::for_each(vec.begin(), vec.end(), f);
}

void main() {
  auto a = new vector<int> { 1, 3, 5, 6, 8, 9, };

  display_vector(*a);

  delete a;

  cout << std::endl <<  "[Press enter to exit]" << std::endl;
  std::cin.ignore();
}