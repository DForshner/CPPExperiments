#include <vector>
#include "BernsteinHash.h"

using namespace std;

template <class T>
unsigned BernsteinHash<T>::Hash(const T& key, std::size_t len)
{
  unsigned int hash = 0;
  unsigned i;

  // It isn't known why 33 seems to work better than other numbers.
  for ( i = 0; i < len; i++ )
    hash = 33 * hash + (unsigned char) key[i];

  return hash;
}

template <class T>
unsigned BernsteinHash<T>::ModifiedHash(const T& key, std::size_t len)
{
  unsigned int hash = 0;
  unsigned i;

  for ( i = 0; i < len; i++ )
    hash = 33 * hash ^ (unsigned char) key[i];

  return hash;
}