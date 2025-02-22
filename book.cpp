//
// Created by Raptor English on 2/18/25.
//

#include "book.h"
#include "product_parser.h"
#include "util.h"

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn_, const std::string author_) :
        Product(category, name, price, qty),
        isbn(isbn_),
        author(author_)
{

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
    return name_ + "\nAuthor: " + author + " ISBN: " + isbn + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left";
}


