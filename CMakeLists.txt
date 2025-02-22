cmake_minimum_required(VERSION 3.28)
project(hw2)

set(CMAKE_CXX_STANDARD 17)

add_executable(hw2 amazon.cpp
        product.cpp
        product.h
        db_parser.cpp
        db_parser.h
        product_parser.cpp
        product_parser.h
        datastore.h
        user.cpp
        user.h
        mydatastore.cpp
        mydatastore.h
        book.h
        book.cpp
        clothing.cpp
        clothing.h
        movie.cpp
        movie.h
        util.cpp
        util.h)
