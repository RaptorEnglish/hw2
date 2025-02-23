#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>
#include <iomanip>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    // initialize new set
    std::set<T> new_set;

    // iterate through s1 and if val is also present in s2, then add it
    for (T x : s1) {
        if (s2.find(x) != s2.end()) {
            new_set.insert(x);
        }
    }

    return new_set;

}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    // initialize new set
    std::set<T> new_set;

    // add both s1 and s2 to the same set
    for (T x : s1) {
        new_set.insert(x);
    }

    for (T x : s2) {
        new_set.insert(x);
    }

    return new_set;
}

// use to format price in print string
std::string format_price(double price);

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
