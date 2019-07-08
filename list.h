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

    struct Item;
    class iterator{
    public:
        explicit iterator(List::Item * it);
        iterator & operator++();
        int & operator*();
        bool operator==(iterator const & it);
        bool operator!=(iterator const & it);

    private:
        List::Item * m_it;
    };
    iterator begin();
    iterator end();

    class const_iterator;
    const_iterator begin() const;
    const_iterator end() const;

private:
    size_t m_count = 0;
    Item * m_head = nullptr;
    Item * m_tail = nullptr;

    void reverse(Item *& item);
};

}// end namespace

