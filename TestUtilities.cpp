#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "TestUtilities.h"
#include <windows.h>
#include <direct.h>
#include <stdio.h>

using namespace std;

unsigned int TestUtilities::hash_vector(vector<string>& v)
{
  std::hash<std::string> hash_fn;
  unsigned int hash = 31;
      
  for (unsigned int i = 0; i < v.size(); i++) {
    hash = hash * 31 + hash_fn(v[i]);
  }
      
  return hash;
}

string TestUtilities::get_current_path()
{
  char cCurrentPath[FILENAME_MAX];
  _getcwd(cCurrentPath, sizeof(cCurrentPath));
  return cCurrentPath;
}