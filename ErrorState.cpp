#include <iostream> // for member class ostream
#include <cstring> // for strcpy(), strlen() function
#include "ErrorState.h" // for header file 

using namespace std;

namespace AMA {
	ErrorState::ErrorState(const char * errorMessage) { // constructor
		if (errorMessage == nullptr) {
			// if address is null, then put it to safe empty state
			m_errState = nullptr;
		}
		else {
			// if not, then allocates dynamic memory and stores the value.
			m_errState = new char[strlen(errorMessage) + 1];
			strcpy(m_errState, errorMessage);
		}
	}
	ErrorState::~ErrorState() { // destructor
		delete[] m_errState; // deallocate the dynamic memory
		m_errState = nullptr;
	}
	void ErrorState::clear() { // member function that clear the message
		delete[] m_errState;
		m_errState=nullptr;
	}
	bool ErrorState::isClear() const { // tester function to see if it is cleared
		// if current object is null, then true, otherwise false
		return m_errState == nullptr;
	}
	void ErrorState::message(const char *str) { // member function that stores the input
		delete[] m_errState; // deallocate the original dynamic memory
		m_errState = new char[strlen(str) + 1]; // allocate a new one based on the input
		strcpy(m_errState, str); // copy the input to current object
	}
	const char* ErrorState::message() const { // member function that access to the member variable
		return m_errState;
	}
	ostream& operator<<(ostream& os, const ErrorState & errorMessage) { // helper function
		if (!errorMessage.isClear()) { 
			// if input is not null, then print it 
			os << errorMessage.message();
		}
		return os; // return a reference
	}
}