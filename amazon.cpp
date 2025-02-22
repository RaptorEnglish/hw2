#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"

#include "mydatastore.h"
#include <set>
#include "book.h"

using namespace std;

/*
ADDED:
    mydatastore.h
    mydatastore.cpp
    book.cpp
    book.h
    clothing.cpp
    clothing.h
    movie.cpp
    movie.h
*/




struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    argc = 2;
    char** args = new char*[2];
    args[0] = argv[0];
    std::string fp = "/Users/raptorenglish/Desktop/USC/2025-SPR/CSCI-104/homework/hw2/database.txt";
    args[1] = new char[fp.size() + 1]; // +1 para el carácter nulo
    std::strcpy(args[1], fp.c_str());
    argv = args;

    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;

    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    // initialize keyword map
    ds.create_keyword_map();

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWUSERS                          " << endl;  // new function
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            } else if ( cmd == "VIEWUSERS" ) {
                ds.print_users();
            } else if ( cmd == "ADD" ) {
                std::string username;
                int hit_result_index;

                // call function to add to cart
                if (ss >> username >> hit_result_index) {
                    ds.add_to_cart(hits, convToLower(username), hit_result_index);
                } else {
                    std::cout << "Invalid input" << std::endl;
                }

            } else if ( cmd == "VIEWCART" ) {
                std::string username;
                if (ss >> username) {
                    ds.view_cart(convToLower(username));
                } else {
                    std::cout << "Need to specify a user." << std::endl;
                }
            } else if ( cmd == "BUYCART" ) {
                std::string username;
                if (ss >> username) {
                    ds.buy_cart(username);
                }
            } else {
                cout << "Unknown command" << endl;
            }
        }

    }

    // free memory

    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
        cout << "No results found!" << endl;
        return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}


