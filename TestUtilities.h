#pragma once

#include <vector>
#include <string>

using namespace std;

class TestUtilities
{
public:

  // Variation of the Berstein hash to combine the std:hash values together
  unsigned int hash_vector(vector<string>& v);

  // Gets the current working path
  string get_current_path();
};