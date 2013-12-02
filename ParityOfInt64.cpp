// Compute the parity of a very large set of 64-bit non-negative integers.
//
// Builds precomputed parity lookup table to avoid re-calculating the parity each time.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <bitset>
#include <vector>
#include <limits>
#include <memory>

using namespace std;

// O(n) where n is length of int.
bool parity(unsigned __int64 val) {
  unsigned __int64 parity = 0;
  while (val) {
    // Get LSB
    bool bit = val & 1UL;
    val = val >> 1;
    // If bit is 1 flip the parity value.
    parity = parity ^ bit;
  }

  return parity;
}

unique_ptr<vector<bool>> build_parity_lookup() {
  auto lookup = unique_ptr<vector<bool>>(new vector<bool>);
  lookup->reserve(_UI16_MAX);

  for (unsigned i = 0; i <= _UI16_MAX; ++i) 
    lookup->push_back(parity(i));

  return lookup;
}

// O(1) lookup
bool parity_fast(const unique_ptr<vector<bool>>& lookup, const unsigned __int64 val) {
  unsigned _int16 mask = 0xFFFFFFFFFFFFFFFFUL;

  return lookup->at(val & mask) ^
    lookup->at(val >> 16 & mask) ^
    lookup->at(val >> 32 & mask) ^
    lookup->at(val >> 48 & mask);
}

void main()
{
  auto lookup = build_parity_lookup();

  unsigned __int64 a = 0x00FF00FF00FF00FE;
  cout << "Value: " << bitset<64>(a) << endl;
  cout << "Parity slow: " << parity(a) << endl;
  cout << "Parity fast: " << parity_fast(lookup, a) << endl;

  unsigned __int64 b = 0xFFFFFFFFFFFFFFFF;
  cout << "Value: " << bitset<64>(b) << endl;
  cout << "Parity slow: " << parity(b) << endl;
  cout << "Parity fast: " << parity_fast(lookup, b) << endl;

  cout << endl << "[Press enter to exit]";
  cin.ignore();
}