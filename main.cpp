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
        pa::List l2;
        l2.reverseUsingRecursion();
        std::cout << l2.getAllItemsInfo();
    }
    {
        using namespace pa;
        pa::List l;
        l.pushFront(1);
        l.pushFront(2);
        l.pushFront(3);
        for (auto it : l) {
            std::cout << it << std::endl;
        }
    }
}
