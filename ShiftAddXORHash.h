#pragma once

#include <string>

using namespace std;

// Shift-Add-XOR hash
// Similar to the rotating hash but rotates the current iterations hash value by different amounts.
//
// Notes: In practice this hash is supposed to perform better than the rotating hash.

template <class T>
class ShiftAddXORHash
{
public:
  unsigned Hash(const T& key, std::size_t len);
};