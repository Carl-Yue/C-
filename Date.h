// Final Project Milestone 1
//
// Version 1.0
// Date
// Author
// Description
//
//
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#ifndef AMA_DATE_H
#define AMA_DATE_H

// error state constant value:
const int NO_ERROR = 0; // No error - the date is valid
const int CIN_FAILED = 1; // istream falied on information entry
const int YEAR_ERROR = 2; // Year value is invalid
const int MON_ERROR = 3; // Month value is invalid
const int DAY_ERROR = 4; // Day value is invalid

namespace AMA {

  // Predefined constants:
  const int min_year = 2000;
  const int max_year = 2030;
  class Date {

	  // member variables:
	  int m_year;
	  int m_month;
	  int m_day;
	  int m_comparator;
	  int m_errorState;
	  // private member functions:
      int mdays(int, int) const;
	  void errCode(int);

  public:
	  // constructors:
	  Date(); // default constructor
	  Date(int, int, int); // 3-argument constructor
	  // operators:
	  bool operator==(const Date&) const;
	  bool operator!=(const Date&) const;
	  bool operator<(const Date&) const;
	  bool operator>(const Date&) const;
	  bool operator<=(const Date&) const;
	  bool operator>=(const Date&) const;
	  // queries and modifier:
	  int errCode() const;
	  bool bad() const;
	  std::istream& read(std::istream&);
	  std::ostream& write(std::ostream&) const;
  };
  // helper functions:
  std::ostream& operator<<(std::ostream&, const Date&);
  std::istream& operator>>(std::istream&, Date&);
}
#endif