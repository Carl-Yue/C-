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
#include <iostream>
#include "Date.h"

using namespace std;

namespace AMA {
  // number of days in month mon_ and year year_
  //
	int Date::mdays(int mon, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}
	void Date::errCode(int errorCode) {
	// input errorCode
		m_errorState = errorCode;
	}
	Date::Date() { // default constructor
		m_year = 0;
		m_month = 0;
		m_day = 0;
		m_comparator = 0;
		m_errorState = NO_ERROR;
	}
	Date::Date(int year, int month, int day) { // 3-argument constructor
		int max_day = mdays(month, year);
		if (year >= min_year && year <= max_year) {
			if (month >= 1 && month <= 12) {
				if (day >= 1 && day <= max_day) {
					m_year = year;
					m_month = month;
					m_day = day;
					m_comparator = year * 372 + month * 13 + day;
					m_errorState = NO_ERROR;
				}
				else {
					m_errorState = DAY_ERROR;
				}
			}
			else {
				m_errorState = MON_ERROR;
			}
		}
		else {
			m_errorState = YEAR_ERROR;
		}
		if (m_errorState != NO_ERROR) {
			m_year = 0;
			m_month = 0;
			m_day = 0;
			m_comparator = 0;
		}
	}
	bool Date::operator==(const Date& rhs) const {
		if (m_errorState != NO_ERROR || rhs.m_errorState != NO_ERROR) {
			return false;
		}
		if (m_comparator == rhs.m_comparator) {
				return true;
		}
		return false;
	}
	bool Date::operator!=(const Date& rhs) const {
		if (m_errorState != NO_ERROR || rhs.m_errorState != NO_ERROR) {
			return false;
		}
		if (m_comparator != rhs.m_comparator) {
			return true;
		}
		return false;
	}
	bool Date::operator<(const Date& rhs) const {
		if (m_errorState != NO_ERROR || rhs.m_errorState != NO_ERROR) {
			return false;
		}
		if (m_comparator < rhs.m_comparator) {
			return true;
		}
		return false;
	}
	bool Date::operator>(const Date& rhs) const {
		if (m_errorState != NO_ERROR || rhs.m_errorState != NO_ERROR) {
			return false;
		}
		if (m_comparator > rhs.m_comparator) {
			return true;
		}
		return false;
	}
	bool Date::operator<=(const Date& rhs) const {
		if (m_errorState != NO_ERROR || rhs.m_errorState != NO_ERROR) {
			return false;
		}
		if (m_comparator <= rhs.m_comparator) {
			return true;
		}
		return false;
	}
	bool Date::operator>=(const Date& rhs) const {
		if (m_errorState != NO_ERROR || rhs.m_errorState != NO_ERROR) {
			return false;
		}
		if (m_comparator >= rhs.m_comparator) {
			return true;
		}
		return false;
	}
	int Date::errCode() const {
		return m_errorState;
	}
	bool Date::bad() const {
		return m_errorState != NO_ERROR;
	}
	std::istream& Date::read(std::istream& istr) {
		int iYear, iMonth, iDay;
		istr >> iYear;
		if (std::cin.get() != '/') {
			m_errorState = CIN_FAILED;
			return istr;
		}
		istr >> iMonth;
		if (std::cin.get() != '/') {
			m_errorState = CIN_FAILED;
			return istr;
		}
		istr >> iDay;
		*this = Date(iYear, iMonth, iDay);
		return istr;
	}
	std::ostream& Date::write(std::ostream& ostr) const {
		ostr << m_year << '/';
		if (m_month < 10) {
			ostr << '0';
		}
		ostr << m_month <<'/';
		if (m_day < 10) {
			ostr << '0';
		}
		ostr << m_day;
		return ostr;
	}
	std::ostream& operator<<(std::ostream& ostr, const Date& date) {
		date.write(ostr);
		return ostr;
	}
	std::istream& operator>>(std::istream& istr, Date& date) {
		date.read(istr);
		return istr;
	}
}
