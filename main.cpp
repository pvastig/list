#include <iostream>

#include "list.h"

int main(int argc, char *argv[])
{
    pa::List l;
    l.pushFront(3);
    l.pushFront(2);
    l.pushFront(1);
    std::cout << l.back() << " " << l.front() << std::endl;
    std::cout << l.getAllItemsInfo();
}
