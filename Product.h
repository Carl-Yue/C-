#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H
#include <iostream>
#include "ErrorState.h"
#include "iProduct.h"

namespace AMA {
	
	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double tax_rate = 0.13;
	
	class Product : public iProduct {
		char m_type;
		char m_sku[max_sku_length];
		char m_unitDes[max_unit_length];
		char* m_name;
		int m_qtyStock;
		int m_qtyNeed;
		double m_price;
		bool m_taxStatus;
		ErrorState m_err;
	
	protected:
		void name(const char* name);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double price() const;
		double cost() const;
		void message(const char* err);
		bool isClear() const;
	public:
		Product(char type = 'N');
		Product(const char* sku, const char* proName, const char* unit, int qtyStock = 0, bool taxStatus = true, double price = 0.00, int qtyNeed = 0);
		Product(const Product& product);
		Product& operator=(const Product& product);
		~Product();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char*) const;
		bool operator>(const iProduct&) const;
		int operator+=(int);
	};
	std::ostream& operator<<(std::ostream&, const iProduct&);
	std::istream& operator>>(std::istream&, iProduct&);
	double operator+=(double&, const iProduct&);
}

#endif 
