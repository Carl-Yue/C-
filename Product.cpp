#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <fstream>
#include <iostream>
#include "Product.h"

using namespace std;

namespace AMA{
	void Product::name(const char* name) {
		if (name == nullptr) {
			delete[] m_name;
			m_name = nullptr;
		}
		else {
			m_name = new char[strlen(name) + 1];
			strcpy(m_name, name);
		}	
	}
	const char* Product::name() const {
		return (m_name == nullptr) ? nullptr : m_name;
		/* if (m_name == nullptr) {
			return nullptr;
		}
		else {
			return m_name;
		} */
	}
	const char* Product::sku() const {
		return m_sku;
	}
	const char* Product::unit() const {
		return m_unitDes;
	}
	bool Product::taxed() const {
		return m_taxStatus;
	}
	double Product::price() const {
		return m_price;
	}
	double Product::cost() const {
		return (taxed()) ? m_price * (1 + tax_rate) : price();
	}
	void Product::message(const char* err) {
		m_err.message(err);
	}
	bool Product::isClear() const {
		return m_err.isClear();
	}
	Product::Product(char type){
		m_type = type;
		m_sku[0] = '\0';
		m_unitDes[0] = '\0';
		m_name = nullptr;
		m_qtyStock = 0;
		m_qtyNeed = 0;
		m_price = 0.0;
		m_taxStatus = true;
		m_err.clear();
	}
	Product::Product(const char * sku, const char * proName, const char * unit, int qtyStock, bool taxStatus, double price, int qtyNeed) {
		*this = Product();
		strcpy(m_sku, sku);
		m_name = nullptr;
		name(proName);
		strcpy(m_unitDes, unit);
		m_qtyStock = qtyStock;
		m_qtyNeed = qtyNeed;
		m_taxStatus = taxStatus;
		m_price = price;
	}
	Product::Product(const Product& product) {
		*this = product;
	}
	Product& Product::operator=(const Product & product)
	{
		if (this != &product) {
			m_type = product.m_type;
			strcpy(m_sku, product.m_sku);
			strcpy(m_unitDes, product.m_unitDes);
			m_qtyStock = product.m_qtyStock;
			m_qtyNeed = product.m_qtyNeed;
			m_price = product.m_price;
			m_taxStatus = product.m_taxStatus;
			m_name = nullptr;
			name(product.m_name);
			if (!product.isClear()) {
				m_err.message(product.m_err.message());
			}
		}
		return *this;
	}
	Product::~Product() {
		delete[] m_name;
		m_name = nullptr;
		m_err.clear();
	}

	std::fstream& Product::store(std::fstream & file, bool newLine) const {
		file << m_type << ',' << m_sku << ',' << m_name << ',' << m_unitDes << ',' << m_taxStatus << ',' << m_price << ',' << m_qtyStock << ',' << m_qtyNeed;
		if (newLine) {
			file << endl;
		}
		return file;
	}

	std::fstream & Product::load(std::fstream & file) {
		char sku[max_sku_length];
		char name[max_name_length];
		char unit[max_unit_length];
		char taxStatus;
		bool tax;
		double price;
		int qtyStock;
		int qtyNeed;
		if (file.is_open()) {
			file.getline(sku, max_sku_length, ',');
			sku[strlen(sku)] = '\0';
			file.getline(name, max_name_length,',');
			name[strlen(name)] = '\0';
			file.getline(unit, max_unit_length, ',');
			unit[strlen(unit)] = '\0';

			file >> taxStatus;
			if ( taxStatus== '1') {
				tax = true;
			}
			else {
				tax = false;
			}
				

			file.ignore();
			file >> price;
			file.ignore();
			file >> qtyStock;
			file.ignore();
			file >> qtyNeed;
			file.ignore();

			*this = Product(sku, name, unit, qtyStock, tax, price, qtyNeed);
		}
		return file;
	}

	std::ostream & Product::write(std::ostream & os, bool linear) const {
		if (!m_err.isClear()) {
			os << m_err.message();
		} 
		else if (linear) {
			os.setf(ios::left);
			os.width(max_sku_length);
			os << m_sku << '|';
			os.width(20);
			os << m_name << '|';
			os.setf(ios::fixed);
			os.width(7);
			os.precision(2);
			os.unsetf(ios::left);
			os.setf(ios::right);
			os << cost() << '|';
			os.width(4);
			os << m_qtyStock << '|';
			os.width(10);
			os.unsetf(ios::right);
			os.setf(ios::left);
			os << m_unitDes << '|';
			os.width(4);
			os.unsetf(ios::left);
			os.setf(ios::right);
			os << m_qtyNeed << '|';
			os.unsetf(ios::right);
		}
		else {
			os << " Sku: " << m_sku << endl;
			os << " Name (no spaces): " << m_name << endl;
			os << " Price: " << m_price << endl;
			if (m_taxStatus) {
				os << " Price after tax: " << cost() << endl;
			}
			else {
				os << " Price after tax: N/A" << endl;
			}
			os << " Quantity On Hand: " << m_qtyStock << ' ' << m_unitDes << endl;
			os << " Quantity needed: " << m_qtyNeed << endl;
		}
		return os;
	}

	std::istream & Product::read(std::istream & is) {
		char sku[max_sku_length];
		char name[max_name_length + 1];
		char unitDes[max_unit_length + 1];
		int qtyStock;
		int qtyNeed;
		double price;
		char taxStatus[2];

		cout << " Sku: ";
		is >> sku;
		cout << " Name (no spaces): ";
		is >> name;
		cout << " Unit: ";
		is >> unitDes;
		cout << " Taxed? (y/n): ";
		is >> taxStatus;

		if (taxStatus[0] != 'y' && taxStatus[0] != 'Y' && taxStatus[0] != 'n' && taxStatus[0] != 'N') {
			m_err.message("Only (Y)es or (N)o are acceptable");
			is.setstate(std::ios::failbit);
			return is;
		}

		cout << " Price: ";
		is >> price;

		if (is.fail()) {
			m_err.clear();
			m_err.message("Invalid Price Entry");
			is.setstate(std::ios::failbit);
			return is;
		}

		cout << " Quantity on hand: ";
		is >> qtyStock;

		if (is.fail()) {
			m_err.clear();
			m_err.message("Invalid Quantity Entry");
			is.setstate(std::ios::failbit);
			return is;
		}

		cout << " Quantity needed: ";
		is >> qtyNeed;
		cin.ignore();

		if (is.fail()) {
			m_err.clear();
			m_err.message("Invalid Quantity Needed Entry");
			is.setstate(std::ios::failbit);
			return is;
		}

		if (!is.fail()) {
			m_err.clear();
		}

		if (!is.fail() && m_err.isClear()) {
			bool tax;
			if (taxStatus[0] == 'y' || taxStatus[0] == 'Y') {
				tax = true;
			}
			else if (taxStatus[0] == 'n' || taxStatus[0] == 'N') {
				tax = false;
			}

			*this = Product(sku, name, unitDes ,qtyStock, tax, price, qtyNeed);
		}
		return is;
	}

	bool Product::operator==(const char* sku) const {
		return strcmp(sku, m_sku);
	}

	double Product::total_cost() const {
		return static_cast<double>(m_qtyStock * cost());
	}
	
	void Product::quantity(int qtyStock) {
		m_qtyStock = qtyStock;
	}

	bool Product::isEmpty() const {
		return m_name == nullptr && m_type == 'N' && m_sku[0] == '\0' && m_unitDes[0] == '\0' && m_qtyStock == 0 && m_qtyNeed == 0 && m_price == 0.00 && m_taxStatus;
	}

	int Product::qtyNeeded() const {
		return m_qtyNeed;
	}

	int Product::quantity() const {
		return m_qtyStock;
	}

	bool Product::operator>(const char* sku) const {
		return strcmp(m_sku,sku)>0;
	}

	bool Product::operator>(const iProduct& product) const {
		return strcmp(m_name, product.name()) > 0;
	}

	int Product::operator+=(int unit) {
		if (unit > 0) {
			return m_qtyStock += unit;
		}
		else {
			return m_qtyStock;
		}
	}

	std::ostream& operator<< (std::ostream& os, const iProduct& product) {
		return product.write(os, true);
	}

	std::istream& operator>> (std::istream& is, iProduct& product) {
		product.read(is);
		return is;
	}

	double operator+=(double& total, const iProduct& product){
		return total + product.total_cost();
	}
}
