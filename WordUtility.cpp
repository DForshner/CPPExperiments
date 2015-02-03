#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <exception>
#include "WordUtility.h"

WordUtility::WordUtility()
{
  open_file();
}

string WordUtility::get_word()
{
  string word;

  if (inFile.good())
    inFile >> word;
  else
  {
    word = "end!";
    reset_file();
  }

  return word;
}

string WordUtility::get_random_word()
{
  string word;

  int r = rand() % 10000; // Assuming 10,000 words in the file

  do
    inFile >> word;
  while ( --r >= 0 ); // Stop the random number deep in the file

  reset_file();

  return word;
}

void WordUtility::reset_file()
{
  inFile.close();
  open_file();
}

void WordUtility::open_file()
{
    inFile.open("../Algorithms.Tests/Utilities/google-10000-english.txt");
  if (!inFile)
    throw std::exception("Unable to open word file.");
}
