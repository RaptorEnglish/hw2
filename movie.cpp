//
// Created by Raptor English on 2/18/25.
//

#include "movie.h"
#include "util.h"

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
    return name_ + "\nGenre: " + genre + " Rating: " + rating + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left";
}
