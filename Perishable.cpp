#include "Perishable.h"

using namespace std;

namespace AMA {

	Perishable::Perishable() : Product('P') {
		m_expiry = Date();
	}

	std::fstream & Perishable::store(std::fstream & file, bool newLine) const {
		Product::store(file, false);
		file << ',' << m_expiry;
		if (newLine) {
			file << "\n";
		}
		return file;
	}
	std::fstream& Perishable::load(std::fstream& file) {
		Product::load(file);
		m_expiry.read(file);
		file.ignore();
		return file;
	}

	std::ostream & Perishable::write(std::ostream & os, bool linear) const {
		Product::write(os, linear);
		if (!Product::isEmpty() && !m_expiry.bad()) {
			if (!linear) {
				os << " Expiry date: " << m_expiry;
			}
			else {
				os << m_expiry;
			}
		}
		return os;
	}
	std::istream& Perishable::read(std::istream& is) {
		is.clear();
		Product::read(is);

		if (m_err.isClear()) {
			cout << " Expiry date (YYYY/MM/DD): ";
			m_expiry.read(is);
		}
		if (m_expiry.errCode() == CIN_FAILED) {
			m_err.clear();
			m_err.message("Invalid Date Entry");
			is.setstate(ios::failbit);
		}
		else if (m_expiry.errCode() == YEAR_ERROR) {
			m_err.clear();
			m_err.message("Invalid Year in Date Entry");
			is.setstate(ios::failbit);
		}
		else if (m_expiry.errCode() == MON_ERROR) {
			m_err.clear();
			m_err.message("Invalid Month in Date Entry");
			is.setstate(ios::failbit);
		}
		else if (m_expiry.errCode() == DAY_ERROR) {
			m_err.clear();
			m_err.message("Invalid Day in Date Entry");
			is.setstate(ios::failbit);
		}
		else {
			m_err.clear();
		}
		return is;
	}
	const Date& Perishable::expiry() const {
		return m_expiry;
	}
}