#include <iostream>

#include "list.h"

int main(int argc, char *argv[])
{
    pa::List l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    std::cout << l.getAllItemsInfo();
    std::cout << l.pop_front();
}
