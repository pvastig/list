#include "list.h"

#include <algorithm>
#include <iostream>

int main(int, char **)
{
    {
        pa::List<int> l;
        l.insert(1);
        l.insert(2);
        l.insert(3);
        l.reverseUsingRecursion();
        std::cout << l.front() << " " << l.back() << std::endl;
        std::cout << l;
        pa::List<int> l2;
        l2.reverseUsingRecursion();
        std::cout << l2;
    }
    {
        using namespace pa;
        pa::List<double> l;
        l.pushFront(1.2);
        l.pushFront(2.5);
        l.pushFront(3.6);
        for (const auto & it : l) {
            std::cout << it << std::endl;
        }
    }
    {
        using namespace pa;
        pa::List l{'a', 'b', 'c' };
        for (auto it : l) {
            std::cout << it << std::endl;
        }

        auto found = std::find(l.begin(), l.end(), 'a');
        std::cout << *found << std::endl;
    }
}
