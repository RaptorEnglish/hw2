//
// Created by Raptor English on 2/18/25.
//

#include "book.h"
#include "product_parser.h"
#include "util.h"
#include <iomanip>

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn_, const std::string author_) :
        Product(category, name, price, qty),
        isbn(isbn_),
        author(author_)
{

}

Book::~Book() {
    // No hay recursos dinámicos que liberar
}


std::set<std::string> Book::keywords() const {
    // extract keywords
    std::set<std::string> terms;

    // add name
    for (const std::string& x : parseStringToWords(name_)) {
        terms.insert(x);
    }

    // add author
    for (const std::string& x : parseStringToWords(author)) {
        terms.insert(x);
    }

    // add isbn
    terms.insert(isbn);

    return terms;
}

std::string Book::displayString() const {
    return name_ + "\nAuthor: " + author + " ISBN: " + isbn + "\n" + format_price(price_) + " " + std::to_string(qty_) + " left.";
}

void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << std::fixed << std::setprecision(2) << price_ << "\n" << qty_ << "\n" << isbn << "\n" << author << std::endl;
}


