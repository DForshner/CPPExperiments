#pragma once

#include <string>

using namespace std;

// XOR Hash
// Repeatedly XORs bytes together.
//
// Notes:
// 1) Doesn't demonstrate the avalanche effect.

template <class T>
class XORHash
{
public:
  unsigned Hash(const T& key, std::size_t len);
};