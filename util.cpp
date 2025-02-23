#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    std::set<std::string> keywords;
    std::string word;

    std::stringstream ss(rawWords);

    // load into word and repeatedly add to a clean word that stores running strings
    while (ss >> word) {
        std::string clean_word;

        for (std::string::iterator it = word.begin(); it != word.end(); it++) {
            if (isalnum(*it)) {
                clean_word += *it;
            } else {
                if (clean_word.size() > 2) {
                    keywords.insert(convToLower(clean_word));
                }
                clean_word.clear();
            }

            // add to keywords
            if (clean_word.size() > 2) {
                keywords.insert(clean_word);
            }
        }
    }

    return keywords;

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
//    s.erase(s.begin(),
//            std::find_if(s.begin(),
//                         s.end(),
//                         std::not1(std::ptr_fun<int, int>(std::isspace))));
//    return s;
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char c) {
        return !std::isspace(c);
    }));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
//    s.erase(
//            std::find_if(s.rbegin(),
//                         s.rend(),
//                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
//            s.end());
//    return s;
    s.erase(
            std::find_if(s.rbegin(), s.rend(), [](unsigned char c) {
                return !std::isspace(c);
            }).base(),
            s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
