#include <vector>
#include "AdditiveHash.h"

using namespace std;

template <class T>
unsigned AdditiveHash<T>::Hash(const T& key, std::size_t len)
{
  unsigned int hash = 0;
  unsigned i;

  for ( i = 0; i < len; i++)
    hash += (unsigned char) key[i];

  return hash;
}

// explicit template instantiations
template class AdditiveHash<string>;
template class AdditiveHash<std::vector<int>>;