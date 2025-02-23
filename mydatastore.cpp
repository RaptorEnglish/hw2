//
// Created by Raptor English on 2/17/25.
//

#include "mydatastore.h"
#include <map>
#include <deque>
#include "util.h"

MyDataStore::~MyDataStore() {
    for (Product* prod : products) {
        delete prod;
    }

    // delete users from map
    for (std::map<std::string, User*>::iterator it = users.begin(); it != users.end(); it++) {
        delete it->second;
    }

}

void MyDataStore::addProduct(Product *p) {
    products.push_back(p);
}

void MyDataStore::addUser(User *u) {
    users[u->getName()] = u;
}


// custom function to create keyword map
void MyDataStore::create_keyword_map() {
    // initialize map
    keyword_map.clear();

    // create map from products
    for (std::vector<Product*>::iterator it = products.begin(); it != products.end(); it++) {
        std::set<std::string> keywords = (*it)->keywords();
        for (std::set<std::string>::iterator it2 = keywords.begin(); it2 != keywords.end(); it2++) {
            keyword_map[*it2].insert(*it);
        }
    }
}

// search through database
std::vector<Product*> MyDataStore::search(std::vector<std::string> &terms, int type) {
    std::vector<Product*> results;

    // exit if no terms
    if (terms.empty()) {
        return results;
    }

    // store all term matches for futher processing
    std::set<Product*> matches;

    // add term matches
    int index = 0;
    for (const std::string& term : terms) {
        if (keyword_map.find(term) != keyword_map.end()) {

            // initialize matches
            if (index == 0) {
                matches = keyword_map[term];
            } else {
                if (type == 0) {  // set intersection
                    matches = setIntersection(matches, keyword_map[term]);
                } else if (type == 1) {  // set union
                    matches = setUnion(matches, keyword_map[term]);
                }
            }

        } else if (type == 0) {
            return results;
        }
        index++;
    }

    // add to set
    for (Product* prod : matches) {
        results.push_back(prod);
    }

    return results;
}

void MyDataStore::dump(std::ostream &ofile) {
    ofile << "<products>" << std::endl;

    // add all product strings to output file
    for (size_t i = 0; i < products.size(); i++) {
        products[i]->dump(ofile);
    }
    ofile << "</products>" << std::endl;

    // add all users to output file
    ofile << "<users>" << std::endl;
    for (std::map<std::string, User*>::iterator it = users.begin(); it != users.end(); it++) {
        it->second->dump(ofile);
    }
    ofile << "</users>" << std::endl;

}

void MyDataStore::add_to_cart(std::vector<Product*> hits, std::string username, size_t hit_result_index) {
    // check that hit size is in bounds
    if (hit_result_index > hits.size() || hit_result_index < 1) {
        std::cout << "Invalid request" << std::endl;
        return;
    }

    // check that username exists
    if (users.find(username) == users.end()) {
        std::cout << "Invalid request" << std::endl;
        return;
    }

    // get item to add
    Product* hit = hits[hit_result_index - 1];

    // add hit to user cart
    all_carts[username].push_back(hit);
    std::cout << "Added to cart " << username << std::endl;

}


void MyDataStore::view_cart(std::string username) {
    if (all_carts.find(username) == all_carts.end()) {
        std::cout << "Invalid username" << std::endl;
        return;
    }

    // get cart
    std::deque<Product*> cart = all_carts[username];

    // print cart
    for (size_t i = 0; i < cart.size(); i++) {
        std::cout << "Item " << i + 1 << ":\n" << cart[i]->displayString() << "\n" << std::endl;
    }

}

void MyDataStore::buy_cart(std::string username) {
    if (all_carts.find(username) == all_carts.end()) {
        std::cout << "Invalid username" << std::endl;
        return;
    }

    // get cart
    std::deque<Product*>& user_cart = all_carts[username];
    User* user = users[username];

    // create new cart
    std::deque<Product*> new_cart;

    // iterate backwards through user cart
    for (std::deque<Product*>::reverse_iterator it = user_cart.rbegin(); it != user_cart.rend(); it++) {
        Product* item = *it;

        if (user->getBalance() >= item->getPrice() && item->getQty() > 0) {  // check user credits
            user->deductAmount(item->getPrice());
            item->subtractQty(1);
        } else {  // add back to cart if cant be purchased
            new_cart.push_back(item);
        }

    }

    // update cart
    all_carts[username] = new_cart;

}


// CUSTOM FUNCTIONS
void MyDataStore::print_products() {
    for (std::vector<Product*>::iterator it = products.begin(); it != products.end(); it++) {
        std::cout << (*it)->getName() << std::endl;
    }
}

void MyDataStore::print_users() {
    for (std::map<std::string, User*>::iterator it = users.begin(); it != users.end(); it++) {
        std::cout << (*it).first << std::endl;
    }
}


