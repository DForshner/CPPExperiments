#pragma once

#include <string>

using namespace std;

// Rotating Hash
// Similar to XOR hash but at each iteration it XORs the current running hash value with itself
// before combing it with the next byte.
//
// Notes:
// 1) It isn't understood why this hash works as well as it does.
// 2) Recommended for short strings.

template <class T>
class BernsteinHash
{
public:
  unsigned Hash(const T& key, std::size_t len);

  // A newer modified version of the algorithm that replaces the addition with an XOR
  unsigned ModifiedHash(const T& key, std::size_t len);
};