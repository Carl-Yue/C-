#ifndef AMA_IPRODUCT_H
#define AMA_IPRODUCT_H
#include <iostream>
#include <fstream>

namespace AMA {
	// iProduct is a abstract class
	class iProduct {
	public:
		// Bool argument will specify whether or not a newline should be inserted after each Iproduct record.
		// Impelmentations will insert the Product records into the fstream object.
		virtual std::fstream& store(std::fstream& file, bool newLine = true) const = 0; 
		// Implementations will extract iProduct records from the fstream object.
		virtual std::fstream& load(std::fstream& file) = 0;
		// Bool argument will specify whether or not the records should be listed on a single line or separate lines.
		// Implementations will insert the iProduct record for the current object into the ostream object.
		virtual std::ostream& write(std::ostream& os, bool linear) const = 0;
		// Implementations will extract the iProduct record for the current object from the istream object.
		virtual std::istream& read(std::istream& is) = 0;
		// It will return true if the string is identical to the stock keeping unit of an iProduct record; false otherwise.
		virtual bool operator==(const char*) const = 0;
		// It will return the cost of a single unit of an iProduc with taxes included.
		virtual double total_cost() const = 0;
		// It will return the address of a C-style null-terminated string containing the name of an iProduct.
		virtual const char* name() const = 0;
		// It will set the number of units available.
		virtual void quantity(int) = 0;
		// It will return the number of units of an iProduct that are needed.
		virtual int qtyNeeded() const = 0;
		// It will return the number of units of an iProduct that are currently available.
		virtual int quantity() const = 0;
		// It will receive an integer identifying the number of units to be added to the iProduct and return the updated unmber of units currently available.
		virtual int operator+=(int) = 0;
		// It will receive an unmodifiable reference to an iProduct object and return true if the current object is greater than the referenced iProduct object; alse otherwise.
		virtual bool operator>(const iProduct&) const = 0;
	};
	// Implementations will insert the iProduct record for the referenced object into the ostream object.
	std::ostream& operator<<(std::ostream&, const iProduct&);
	// Implementations will extract the iProduct record for the referenced object from the istream object.
	std::istream& operator>>(std::istream&, iProduct&);
	// Implementations will add the total cost of the iProduct object to the double received and return the updated value of the double.
	double operator+=(double&, const iProduct&);
	// It will return the address of a Product object.
	iProduct* CreateProduct();
	// It will return the address of a Perishable object.
	iProduct* CreatePerishable();
}

#endif