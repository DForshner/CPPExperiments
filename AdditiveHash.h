#pragma once

#include <string>

using namespace std;

// Additive Hash
// A very poor hash implementation that sums the char values of a string together.
//
// Problems:
// 1) Stings with the same characters in different order will give the same hash value. 
// Example: rats/star/arts/tars all give a hash of 442.
// 2) Doesn't demonstrate the avalanche effect so two strings that are similar can have similar
// hash values.

template <class T>
class AdditiveHash
{
public:  
  unsigned Hash(const T& key, std::size_t len);
};