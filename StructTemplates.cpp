#include <iostream>
#include <assert.h>

// Compiler: Microsoft Visual C++ Compiler Nov 2012 CTP (v120_CTP_Nov2012)

using namespace std;

// Class template
template<class Type1, class Type2>
struct KeyValuePair
{
	Type1 first;
	Type2 second;

	// Parameterized constructor with optional parameters.
	KeyValuePair(const Type1& t1 = Type1(), const Type2& t2 = Type2()) :
		first(t1),
		second(t2)
		{}

	// Copy-constructor
	KeyValuePair(const KeyValuePair<Type1, Type2>& KeyValuePairToCopy) : 
		first(KeyValuePairToCopy.first),
		second(KeyValuePairToCopy.second)
		{}

	bool operator == (const KeyValuePair<Type1, Type2>& KeyValuePairToCompare) const // Declaring a member function with the const keyword specifies that the function is a "read-only" function that does not modify the object for which it is called.
	{
	  return first == KeyValuePairToCompare.first && 
			 second == KeyValuePairToCompare.second;
	}

	KeyValuePair<Type1, Type2> operator + (const KeyValuePair<Type1, Type2>& KeyValuePairToCompare) const
	{
	  return KeyValuePair(first + KeyValuePairToCompare.first, second + KeyValuePairToCompare.second);
	}

	KeyValuePair<Type1, Type2> operator - (const KeyValuePair<Type1, Type2>& KeyValuePairToCompare) const
	{
	  return KeyValuePair(first - KeyValuePairToCompare.first, second - KeyValuePairToCompare.second);
	}
};

int main(){

	KeyValuePair<int,int> point1; // The instantiation of a class template is a template class.  point1 is an object of the KeyValuePair<int,int> template class.
	point1.first = 10;
	point1.second = 20;
	assert(point1.first == 10);
	assert(point1.second == 20);

	KeyValuePair<int, double> intDoublePair = KeyValuePair<int, double>(90, 9.4868329);
	assert(intDoublePair.first == 90);
	assert(intDoublePair.second == 9.4868329);

	KeyValuePair<int,int> point2(point1);
	assert(point1.first == point2.first);
	assert(point1.second == point2.second);

	KeyValuePair<int,int> point3 = point1 - point2;
	assert(point3.first == 0);
	assert(point3.second == 0);

	return 0;
}