#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

class WordUtility
{
private:
  ifstream inFile;
  void open_file();
  void reset_file();

public:

  // Constructor
  WordUtility();
  
  // Destructor
  ~WordUtility() { inFile.close(); } 

  // Returns a single word
  string get_word();

  // Returns a random word
  string get_random_word();
};