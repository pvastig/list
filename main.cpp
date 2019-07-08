#include <iostream>

#include "list.h"

int main(int argc, char *argv[])
{
    {
        pa::List<int> l;
        l.insert(1);
        l.insert(2);
        l.insert(3);
        l.reverseUsingRecursion();
        std::cout << l.front() << " " << l.back() << std::endl;
        std::cout << l.getAllItemsInfo();
        pa::List<int> l2;
        l2.reverseUsingRecursion();
        std::cout << l2.getAllItemsInfo();
    }
    {
        using namespace pa;
        pa::List<double> l;
        l.pushFront(1.2);
        l.pushFront(2.5);
        l.pushFront(3.6);
        for (auto it : l) {
            std::cout << it << std::endl;
        }
    }
    {
        using namespace pa;
        pa::List<char> l{'a', 'b', 'c' };
        for (auto it : l) {
            std::cout << it << std::endl;
        }
    }
}
