//
// Created by Raptor English on 2/18/25.
//

#include "clothing.h"
#include "util.h"
#include <iomanip>

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size_, std::string brand_) :
        Product(category, name, price, qty),
        size(size_),
        brand(brand_)
{

}

std::set<std::string> Clothing::keywords() const {
    // extract keywords
    std::set<std::string> terms;

    // add name
    for (const std::string& x : parseStringToWords(name_)) {
        terms.insert(x);
    }

    // add author
    for (const std::string& x : parseStringToWords(brand)) {
        terms.insert(x);
    }

    return terms;
}

std::string Clothing::displayString() const {
    return name_ + "\nSize: " + size + " Brand: " + brand + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}

void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << std::fixed << std::setprecision(2) << price_ << "\n" << qty_ << "\n" << size << "\n" << brand << std::endl;
}
