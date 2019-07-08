#include <iostream>

#include "list.h"

int main(int argc, char *argv[])
{
    {
        pa::List l;
        l.insert(1);
        l.insert(2);
        l.insert(3);
        l.reverseUsingRecursion();
        std::cout << l.front() << " " << l.back() << std::endl;
        std::cout << l.getAllItemsInfo();
    }
    {
        pa::List l;
        l.pushFront(1);
        l.pushFront(2);
        l.pushFront(3);
        l.reverse();
    }
}
