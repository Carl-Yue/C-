// header file safeguard
#ifndef AMA_ERRORSTATE_H
#define AMA_ERRORSTATE_H
#include <iostream>

using namespace std;
namespace AMA {
	class ErrorState {
		char* m_errState;
	public:
		explicit ErrorState(const char* errorMessage = nullptr); // constructor
		ErrorState(const ErrorState& em) = delete; // deleted copy constructor
		ErrorState& operator=(const ErrorState& em) = delete; // deleted copy operator
		virtual ~ErrorState(); // destructor
		void clear(); // member function that clear the message
		bool isClear() const; // tester function to see if it is cleared
		void message(const char*); // member function that stores the input
		const char* message() const; // member function that access to the member variable
	};
	ostream& operator<< (ostream&, const ErrorState&); // helper operator function
}
#endif