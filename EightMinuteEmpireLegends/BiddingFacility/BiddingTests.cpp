#include "BiddingTests.h"
#include "NameSorter.h"

#include <iostream>


int main(int argc, char** argv) {

    NameSorter nameSorter;

    nameSorter.addName("Bob");
    nameSorter.addName("Carol");
    nameSorter.addName("Alice");

    std::cout << nameSorter.getLeader();
    return 0;
}