#include <iostream>
#include <assert.h>

// Compiler: Microsoft Visual C++ Compiler Nov 2012 CTP (v120_CTP_Nov2012)

using namespace std;

// Function-template.  T is the template type parameter.
template<typename T> 
T Triple(const T data)
{
   return data * 3;
}

// Reference to object that is modified.
template<class T>
void TripleAndModify(T& data) // const prevents the method from modifying the argument.
{
    data *= 3;
}

// Reference to object passed returning result.
template<class T>
T TripleAndReturn(const T& data) // const prevents the method from modifying the argument.
{
    return data * 3;
}

// Template type arguments mixed with non-template type arguments.
// We could also use (const T1* tArray, ...) instead of tArray[] when passing an array.
template<class T>
double GetAverage(const T tArray[], const int len) 
{
    T tSum = T(); // Call default constructor for data type.

    for (int nIndex = 0; nIndex < len; ++nIndex)
    {
        tSum += tArray[nIndex];
    }

    // Whatever type of T is, convert to double
    return double(tSum) / len;
}

// Multiple same Type
template<class T>
T Max(T t1, T t2)
{
   if (t1 > t2)
      return t1;
   return t2;
}

// Multiple different Type
template<class T1, class T2>
bool FirstGreaterThanSecond(const T1& t1, const T2& t2)
{
   if (t1 > t2)
      return true;
   return false;
}

template<class T>
void PrintNumbers(T array[], int array_size, T filter = T()) // Optional argument with TYPE T's default constructor T()
{
   for(int nIndex = 0; nIndex < array_size; ++nIndex)
   {
       if ( array[nIndex] != filter)
           cout << array[nIndex];
   }
   cout << endl;
}

int main(){
	assert( Triple(20) == 60); // Int
	
	assert( Triple( Triple(2.22) ) == 19.98000); // Double

	float x = 50;
	TripleAndModify(x);
	assert( x = 150.000000);

	x = 50;
	float y = TripleAndReturn(x);
	assert( x = 50.000000);
	assert( y = 150.000000);

	int IntArray[5] = {100, 200, 400, 500, 1000};
	int average =  GetAverage(IntArray, 5);
	assert ( average == 440 );

    float FloatArray[3] = { 1.55f, 5.44f, 12.36f};
	float averageFloat =  GetAverage(FloatArray, 3);
	//assert ( averageFloat == 6.44999933 );
		
	int max = Max(5, 10);
	assert ( max == 10 );

	bool shouldBeTrue = FirstGreaterThanSecond(7, 1);
	assert ( shouldBeTrue == true );

	int Array[10] = {1,2,0,3,4,2,5,6,0,7};
	PrintNumbers(Array, 10);
	PrintNumbers(Array, 10, 4);

	return 0;
}