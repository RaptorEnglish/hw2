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
    ~Book() override; // Destructor

    std::set<std::string> keywords() const override;

    std::string displayString() const;

    void dump(std::ostream& os) const;

};

#endif //HW2_BOOK_H
