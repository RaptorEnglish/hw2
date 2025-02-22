//
// Created by Raptor English on 2/18/25.
//

#ifndef HW2_BOOK_H
#define HW2_BOOK_H

#include "product.h"


class Book : public Product {
private:
    std::string isbn;
    std::string author;
public:
    Book(const std::string category, const std::string name, double price, int qty, const std::string isbn_, const std::string author_);

    std::set<std::string> keywords() const;

    std::string displayString() const;
};

#endif //HW2_BOOK_H
