#pragma once

#include <string>

using namespace std;

// Rotating Hash
// Similar to XOR hash but at each iteration it XORs the current running hash value with itself
// before combing it with the next byte.
//
// Notes:
// 1) The extra step provides a better distribution than the XOR hash.

template <class T>
class RotatingHash
{
public:
  unsigned Hash(const T& key, std::size_t len);
};