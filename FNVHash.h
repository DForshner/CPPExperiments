#pragma once

#include <string>

using namespace std;

// Fowler-Noll-Vo hash
// Similar to XOR hash but at each iteration it XORs the current running hash value with itself
// before combing it with the next byte.
//
// Notes:
// 1) One of the more popular hashing functions.
// 2) Similar to Bernstein hash but with different constants.

template <class T>
class FNVHash
{
public:
  unsigned Hash(const T& key, std::size_t len);
};