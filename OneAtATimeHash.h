#pragma once

#include <string>

using namespace std;

// One-at-a-Time Hash
// Designed by Bob Jenkins.
//
// Notes:
// 1) Demonstrates the avalanche effect.

template <class T>
class OneAtATimeHash
{
public:
  unsigned Hash(const T& key, std::size_t len);
};