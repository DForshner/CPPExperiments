// Move Semantics/Constructors Tutorial
//
// From: http://www.cprogramming.com/c++11/rvalue-references-and-move-semantics-in-c++11.html
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

namespace Test {

  vector<int> doubleValues(const vector<int>& v) {
    vector<int> new_values; // Constructs new vector new_values
    new_values.reserve(v.size());
    for (auto s = v.begin(), e = v.end(); s != e; ++s) {
      new_values.push_back(2 * *s);
    }

    return new_values; // In C++03 the entire vector would be copied
  }
    
  // Accepts "Permanent" lvalue
  void printReference(const string& str) { cout << "lvalue (Permanent) Name: " << str << endl; }
    
  // Accepts "Temporary" rvalue
  void printReference(string&& str) { cout << "rvalue (Temporary) Name: " << str << endl; }

  class MetaData {
  public:
    MetaData(const string& name) : _name(name) {}
    MetaData(const MetaData& that) : _name(that._name) { cout << endl << "MetaData - Copy " << endl;  }
    MetaData(MetaData&& that) : _name(move(that._name)) { // std:move allows the strings move constructor to be called.
      cout << endl << "MetaData - Move" << endl;
      //that._name = nullptr;
    }
    string getName() const { return _name; }
  private:
    string _name;
  };

  class ArrayWrapper {
  public:
    // Default Constructor
    ArrayWrapper() : _p_vals(new int[64]), _size(64), _metaData("ArrayWrapper") {} 

    ArrayWrapper(int n) : _p_vals(new int[n]), _size(n), _metaData("ArrayWrapper") {}

    // Copy Constructor - Allocate memory and copy every value from the array one at a time.
    ArrayWrapper(const ArrayWrapper& that) 
      : _p_vals(new int[that._size]), _size(that._size), _metaData(that._metaData) {
      for (auto i = 0; i < _size; ++i) { _p_vals[i] = that._p_vals[i]; }
      cout << "ArrayWrapper - Copy" << endl;
    }

    // Move Constructor - Copy any primitive fields and transfer ownership of any pointer fields.
    // Avoid a copy by changing the original, temporary object.
    ArrayWrapper(ArrayWrapper&& that) 
      : _p_vals(that._p_vals), _size(that._size), 
      //_metaData(that._metaData) - Would not call MetaData's move constructor! 
      _metaData(move(that._metaData)) { // std::move converts a lvalue to a rvalue so the move constructor can be invoked.
      // Null out the pointer of the temporary object or when it goes out of scope its destructor will free the array we moved.
      that._p_vals = nullptr; 
      that._size = 0;
      cout << "ArrayWrapper - Move" << endl;
    }

    ~ArrayWrapper() { delete [] _p_vals; }
    void insert(int value, int index) { _p_vals[index] = value; }

  private:
    int * _p_vals;
    int _size;
    MetaData _metaData;
  };
}

int main()
{
  vector<int> vals;
  vals.reserve(100);
  int n(0);
  generate_n(back_inserter(vals), 100, [n]()mutable { return n++; });

  auto vals2 = Test::doubleValues(vals);
  cout << "Doubled Array: " << endl;
  for (const auto &k : vals2) { cout << k << " "; }
  cout << endl << endl;

  string cat("Bob");
  auto getCat = []() -> string { return "Charles"; };

  Test::printReference(cat); // Goes to lvalue reference overload.
  Test::printReference(getCat()); // Since function returns a temporary value it goes to rvalue reference overload.

  Test::ArrayWrapper a1;
  a1.insert(5, 0);
  a1.insert(10, 1);

  cout << "Copying A1 to A2" << endl;
  auto a2 = a1;

  auto getArray = []() -> Test::ArrayWrapper { 
    Test::ArrayWrapper temp;
    temp.insert(5, 0);
    temp.insert(10, 1);
    return temp;
  };
  cout << "Moving rvalue array to A3" << endl;
  auto a3 = getArray();

  cout << endl << "[Press enter to exit]" << endl;
  cin.ignore();
  return 0;
}