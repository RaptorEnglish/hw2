//
// Created by Raptor English on 2/18/25.
//

#ifndef HW2_MOVIE_H
#define HW2_MOVIE_H

#include "product.h"

class Movie : public Product {
private:
    std::string genre;
    std::string rating;
public:
    Movie(const std::string category, const std::string name, double price, int qty, std::string genre_, std::string rating_);

    std::set<std::string> keywords() const;

    std::string displayString() const;
};

#endif //HW2_MOVIE_H
