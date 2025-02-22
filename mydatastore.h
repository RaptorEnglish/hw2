//
// Created by Raptor English on 2/17/25.
//

#include "datastore.h"
#include <map>
#include <vector>
#include <deque>

#ifndef HW2_MYDATASTORE_H
#define HW2_MYDATASTORE_H

class MyDataStore : public DataStore {
private:
    std::vector<Product*> products;
//    std::vector<User*> users;
    std::map<std::string, User*> users;
    std::map<std::string, std::set<Product*>> keyword_map;

    std::map<std::string, std::deque<Product*>> all_carts;

public:
    // destructor
    ~MyDataStore();

    void addProduct(Product* p) override;

    void addUser(User* u) override;

    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;

    void dump(std::ostream& ofile) override;

    void add_to_cart(std::vector<Product*> hits, std::string username, int hit_result_index);

    void view_cart(std::string username);

    void buy_cart(std::string username);


    // custom functions
    void print_products();
    void print_users();
    void create_keyword_map();

};

#endif //HW2_MYDATASTORE_H
