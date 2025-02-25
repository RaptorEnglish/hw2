//
// Created by Raptor English on 2/18/25.
//

#include "movie.h"
#include "util.h"
#include <iomanip>

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre_, std::string rating_) :
        Product(category, name, price, qty),
        genre(genre_),
        rating(rating_)
{

}


std::set<std::string> Movie::keywords() const {
    // extract keywords
    std::set<std::string> terms;

    // add name
    for (const std::string& x : parseStringToWords(name_)) {
        terms.insert(x);
    }

    // add author
    for (const std::string& x : parseStringToWords(genre)) {
        terms.insert(x);
    }

    return terms;
}

std::string Movie::displayString() const {
    return name_ + "\nGenre: " + genre + " Rating: " + rating + "\n" + format_price(price_) + " " + std::to_string(qty_) + " left.";
}


void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << std::fixed << std::setprecision(2) << price_ << "\n" << qty_ << "\n" << genre << "\n" << rating << std::endl;
}