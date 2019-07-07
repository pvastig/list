#include <iostream>

#include "list.h"

int main(int argc, char *argv[])
{
    pa::List l;
    l.insert(1);
    l.insert(2);
    l.insert(3);
    std::cout << l.getAllItemsInfo();
}
