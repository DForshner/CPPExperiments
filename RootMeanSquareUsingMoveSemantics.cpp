// Calculates the root mean square of a vector of numbers using move semantics.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <array>

using namespace std;

double sum(const vector<double>& v) {
  return accumulate(v.cbegin(), v.cend(), 0.0l, plus<double>());
}

double mean(const vector<double>& v) {
  return sum(v) / static_cast<double>(v.size());
}

// Mutates the vector squaring the values.
vector<double> squared(vector<double>&& v) {
  transform(v.begin(), v.end(), v.begin(), [](double n) { return n * n; });
  return v;
}

double root_mean_square(vector<double>&& v) {
  return sqrt(mean(squared(move(v))));
}

int main() {
  // Since {1,2,3} is temporary it is an rvalue.
  cout << root_mean_square({ 1, 2, 3 }) << endl;

  // Since we aren't going to use temp again we tell the compiler its and rvalue.
  vector<double> temp = { 1, 2, 3 };
  cout << root_mean_square(move(temp));

  // If we are going to need a vector again we can make a copy.
  vector<double> permenant = { 1, 2, 3 };
  cout << root_mean_square(vector<double>(permenant));

  cout << endl << "[Press enter to exit]" << endl;
  cin.ignore();
  return 0;
}