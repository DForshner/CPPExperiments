#include <iostream>
#include <assert.h>

// Compiler: Microsoft Visual C++ Compiler Nov 2012 CTP (v120_CTP_Nov2012)

using namespace std;

// Use a class template to define an abstract type 
// whose behaviour is generic and is reusable, adaptable.
template<class T>
class Item
{
	public:
		Item() : Data( T() )
		{}

		void SetData(T nValue)
		{
			Data = nValue;
		}

		void PrintData()
		{
			cout << Data << endl;
		}

		void PrintDataOnlyWorksForInt()
		{
			cout << Data  % 10 << endl;
		}

	private:
		T Data;
};

// SIZE is a non-type template argument.
// Can only use int, char, long, long long, unsigned, and enums.
template<class T, int SIZE> 
class Array
{
	static const int Elements_2x = SIZE * 2; // Use static-constant values to initialize the class.

public:
	void Initialize()
	{ 
		for(int nIndex = 0; nIndex < SIZE; ++nIndex)
			TheArray[nIndex] = T();
	}

	void GetDefaultValue(int arg = SIZE); // use static-constant value to set a default parameter of a function.

	// Array-element access operator to get/read the element.
	T operator[](int nIndex) const
	{
	  if (nIndex > 0 && nIndex < SIZE)
	  {
		return TheArray[nIndex];
	  }
	  return T(); // Return default value for type
	}

	T& operator[](int nIndex) // Returns a reference of an element which can be modified by the caller.
	{
		assert(nIndex > 0 && nIndex < SIZE)
		return TheArray[nIndex];
	}

	T LogicalSum() const
	{
		T sum = T();

		for(int nIndex = 0; nIndex < SIZE; ++nIndex)
		{
			sum += TheArray[nIndex]; // Will require += to be available for target type T
		}
		return sum;
	}

private:
	T TheArray[SIZE];
};

int main(){

	cout << "Start!" << endl;

	Item<int> item1; // For class templates you have to explicitly pass template types.
	item1.SetData(120);
	item1.PrintData();
	item1.PrintDataOnlyWorksForInt();

	Item<float> item2;
	item2.SetData(120.0);
	item2.PrintData();
	//item2.PrintDataOnlyWorksForInt(); // Will cause error during phase-two compilation when the code actually gets fully-compiled against the type for which it is being instantiated.

	Array<int, 10> testArray;

	cout << "End!" << endl;

	return 0;
}