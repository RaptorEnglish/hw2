//
// Created by Raptor English on 2/18/25.
//

#ifndef HW2_CLOTHING_H
#define HW2_CLOTHING_H

#include "product.h"


class Clothing : public Product {
private:
    std::string size;
    std::string brand;
public:
    Clothing(const std::string category, const std::string name, double price, int qty, std::string size_, std::string brand);

    std::set<std::string> keywords() const;

    std::string displayString() const;
};

#endif //HW2_CLOTHING_H
