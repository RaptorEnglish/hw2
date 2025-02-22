//
// Created by Raptor English on 2/17/25.
//

#include "mydatastore.h"
#include <map>
#include <deque>

MyDataStore::~MyDataStore() {

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
    for (auto& prod : products) {
        for (auto& keyword : prod->keywords()) {
            keyword_map[keyword].insert(prod);
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
    std::vector<std::set<Product*>> term_matches;

    // update term matches
    for (const std::string& term : terms) {
        auto it = keyword_map.find(term);
        if (it != keyword_map.end()) {
            term_matches.push_back(keyword_map[term]);
        } else if (type == 0) {
            // no results if using AND and nothing found
            return results;
        }
    }

    // handle AND search with intersection
    if (type == 0) {  // intersection set
        std::set<Product*> intersection_set = term_matches[0];

        // update intersection set
        for (size_t i = 1; i < term_matches.size(); i++) {
            std::set<Product *> temp;
            std::set_intersection(intersection_set.begin(), intersection_set.end(),
                                  term_matches[i].begin(), term_matches[i].end(),
                                  std::inserter(temp, temp.begin()));
            intersection_set = temp;
        }

        // convert to vector
        results.assign(intersection_set.begin(), intersection_set.end());

    } else {  // handle OR search with union
        std::set<Product*> union_set;
        for (std::set<Product*> match : term_matches) {
            union_set.insert(match.begin(), match.end());
        }
        results.assign(union_set.begin(), union_set.end());
    }

    return results;
}

void MyDataStore::dump(std::ostream &ofile) {

}

void MyDataStore::add_to_cart(std::vector<Product*> hits, std::string username, int hit_result_index) {
    // check that hit size is in bounds
    if (hit_result_index >= hits.size() || hit_result_index < 0) {
        std::cout << "Out of bounds" << std::endl;
        return;
    }

    // check that username exists
    if (users.find(username) == users.end()) {
        std::cout << "User not found" << std::endl;
        return;
    }

    // get item to add
    Product* hit = hits[hit_result_index];

    // add hit to user cart
    all_carts[username].push_front(hit);
    std::cout << "Added to cart " << username << std::endl;

}


void MyDataStore::view_cart(std::string username) {
    if (all_carts.find(username) == all_carts.end()) {
        std::cout << "Invalid username" << std::endl;
        return;
    }

    // get cart
    std::deque<Product*> cart = all_carts[username];

    std::cout << "User Cart" << std::endl;

    // print cart
    int i = 1;
    for (auto prod : cart) {
        std::cout << "Item " << i << ":\n" << prod->displayString() << "\n" << std::endl;
        i++;
    }

    std::cout << std::endl;

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
    for (auto it = user_cart.rbegin(); it != user_cart.rend(); it++) {
        Product* item = *it;

        if (!item->getQty()) {  // if item doesn't have qty, move to next
            std::cout << "Could not buy " << item->getName() << std::endl;
            new_cart.push_back(item);
        } else if (user->getBalance() >= item->getPrice()) {  // check user credits
            user->deductAmount(item->getPrice());
            item->subtractQty(1);
            std::cout << "Buying " << item->getName() << std::endl;
        } else {  // add back to cart if cant be purchased
            std::cout << "Could not buy " << item->getName() << std::endl;
            new_cart.push_back(item);
        }

    }

    // update cart
    all_carts[username] = new_cart;

}


// CUSTOM FUNCTIONS
void MyDataStore::print_products() {
    for (const auto& x : this->products) {
        std::cout << x->getName() << std::endl;
    }
}

void MyDataStore::print_users() {
    for (const auto& x : this->users) {
        std::cout << x.first << std::endl;
    }
}


