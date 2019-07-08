#pragma once

#include <string>

namespace pa {

class List
{
    friend void swap(List & l, List & r) noexcept;
public:
    List();
    List(const List & other);
    List(List && other);
    List & operator=(List other);
    ~List();

    void addList(const List & src);

    void pushFront(int value);
    void pushBack (int value);

    int popFront();
    int popBack ();

    bool remove(int value);
    void insert(int value);

    void reverse();
    void reverseUsingRecursion();

    int & front();
    const int & front() const;

    int & back();
    const int & back() const;

    size_t size() const { return m_count; }
    std::string getAllItemsInfo() const;

    bool empty() const { return m_count == 0; }

private:
    struct Item
    {
        int value;
        Item * next;
        Item(int value, Item * next = nullptr) : value(value), next(next) {}
    };

    void reverse(Item *& item);

    size_t m_count = 0;
    Item * m_head = nullptr;
    Item * m_tail = nullptr;
};

}// end namespace

