#include <string>
#include <iostream>
#include <map>
#include <utility>

// Compiler: Microsoft Visual C++ Compiler Nov 2012 CTP (v120_CTP_Nov2012)

using namespace std;

void FillList(map<int, string>& list){
	list[0] = "item1"; // Using array index notation
	list[1] = "item2";
	list[2] = "item3";
}

int main(){	
	map<int, string> myList; // STL map

	FillList(myList);

	auto listIterator = myList.begin(); // Same as saying map<int, string>::iterator listIterator = myList.begin();

	for ( auto listItem : myList ) // Ranged for loop
	{
		cout << listItem.first << " = " << listItem.second << endl;
	}

	return 0;
}