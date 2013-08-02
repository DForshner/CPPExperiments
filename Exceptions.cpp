#include <iostream>
#include <assert.h>
#include <exception>

// Compiler: Microsoft Visual C++ Compiler Nov 2012 CTP (v120_CTP_Nov2012)

using namespace std;

// Exception specifications
int OnlyIntExceptionsAllowed (int param) throw (int) {
	//throw (float) 3.1415; // Would compile but cause exception.
	return param;
}

float NoExceptionsAllowed (float param) throw() {
	// throw 1;  // Would compile but cause exception.
	return param;
}

double AllExceptionsAllowed (double param) {
	return param;
}

// Custom exception
class CustomException: public exception
{
	virtual const char* what() const throw()
	{
		return "Custom Exception";
	}

} CustomException;

int main () {

	// Simple exceptions
	try {
		throw 1;
	}
	catch (int e) { // The type of the argument passed by the throw expression is checked against the exception.
		cout << "An int exception occurred." << endl;
	}

	// Default catch
	try {
		throw "Error";
	}
	catch (int e) {
		cout << "An int exception occurred." << endl;
	}
	catch (...) { // Will catch any type of exception.
		cout << "An unknown exception occurred." << endl;
	}

	OnlyIntExceptionsAllowed(33);
	NoExceptionsAllowed(11);

	// Nesting Exceptions.
	try {
		try {
			throw "Internal error.";
		}
		catch (int n) {
			throw; // The internal catch block forwards the exception to the external level.
		}
	}
	catch (...) {
		cout << "Nested exception: " << endl;
	}

	// Custom exceptions
	try {
		throw CustomException;
	}
	catch (exception& e) { // Handler that catches exception objects by reference.  Catches all classes derived from type exception.
		cout << "Custom exception: " << e.what() << endl;
	}

	return 0;
}