// Iterators demo
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <vector>

using namespace std;

class IntVector; // Forward declaration
  
class Iter {
public:
  Iter(const IntVector* p_vec, int pos) : _pos(pos), _p_vec(p_vec) {}
  bool operator != (const Iter& that) const {
    return _pos != that._pos;
  }
  int operator* () const; // Can't define method until after IntVector is defined;
  const Iter& operator++ () {
    ++_pos;
    return *this;
  }
private:
  int _pos;
  const IntVector *_p_vec;
};

class IntVector {
public:
  IntVector() {}
  int get(int col) const { return _data[col]; }
  Iter begin() const { return Iter(this, 0); }
  Iter end() const { return Iter(this, 100); }
  void set(int index, int val) { _data[index] = val; }
private:
  int _data[100];
};
  
int Iter::operator* () const { return _p_vec->get(_pos); } // Fill in the method definition.

int main() {
  // Vector's random access iterator
  vector<int> intVector;
  intVector.push_back(1);
  intVector.push_back(2);
  intVector.push_back(3);
  cout << endl << "const iterator values: ";
  for (auto iter = intVector.cbegin(); iter != intVector.cend(); iter++) {
    cout << *iter;
    //(*iter)++; // Can't be done because .cbegin returns const iterator.
  }

  cout << endl << "iterator values: ";
  for (auto iter = intVector.begin(); iter != intVector.cend(); iter++) {
    cout << *iter;
    (*iter) *= 10;
  }

  // The random access iterator can be used to access the nth item.
  cout << endl << "Random access iterator: "
    << *(intVector.cbegin() + 0)
    << *(intVector.cbegin() + 1)
    << *(intVector.cbegin() + 2);
    // << *(intVector.cbegin() + 3); -- Crashes because out of range.  Iterators do not provide bounds checking.

  // Iterators can be used to operate on a range of values.
  intVector.erase(intVector.cbegin(), intVector.cbegin() + 1);

  cout << endl << "After .erase(): ";
  for (const auto &i : intVector) { cout << i; }

  cout << endl << "Custom iterator: ";
    IntVector v;
    for (auto i = 0; i < 100; i++) {
      v.set(i, i);
    }
    for (const auto i : v) { cout << i; }

  cout << endl << "[Press enter to exit]" << endl;
  cin.ignore();
  return 0;
}