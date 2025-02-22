CXX=g++
CXXFLAGS=-g -Wall -std=c++11
# Uncomment for parser DEBUG
#DEFS=-DDEBUG

OBJS=amazon.o user.o product.o util.o book.o movie.o clothing.o product_parser.o db_parser.o mydatastore.o

all: amazon
	./amazon database.txt

amazon: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)

amazon.o: amazon.cpp product.h mydatastore.h util.h product_parser.h db_parser.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c amazon.cpp

user.o: user.cpp user.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c user.cpp


# Compile the diff products
product.o: product.cpp product.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c product.cpp

book.o: book.cpp book.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c book.cpp

clothing.o: clothing.cpp clothing.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c clothing.cpp

movie.o: movie.cpp movie.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c movie.cpp


# Compile data stores
mydatastore.o: mydatastore.cpp mydatastore.h datastore.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c mydatastore.cpp

db_parser.o: db_parser.cpp db_parser.h product.h product_parser.h user.h datastore.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c db_parser.cpp

product_parser.o: product_parser.cpp product_parser.h product.h book.h clothing.h movie.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c product_parser.cpp

util.o: util.cpp util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c util.cpp

# clean up project
clean:
	rm -f *.o amazon