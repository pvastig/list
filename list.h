#pragma once

#include <initializer_list>
#include <iostream>
#include <sstream>
#include <string>

namespace pa {

template<class T>
class List
{
    template<T const &> //TODO: issue https://stackoverflow.com/questions/2183087/why-cant-i-use-float-value-as-a-template-parameter
    friend void swap(List<T> & l, List<T> & r) noexcept;
public:
    List();
    explicit List(std::initializer_list<T> args);
    List(const List & other);
    List(List && other) noexcept;
    List & operator=(List other);
    ~List();

    void addList(const List & src);

    void pushFront(T value);
    void pushBack (T value);

    T popFront();
    T popBack ();

    bool remove(T value);
    void insert(T value);

    void reverse();
    void reverseUsingRecursion();

    T & front();
    const T & front() const;

    T & back();
    const T & back() const;

    size_t size() const { return m_count; }
    std::string getAllItemsInfo() const;

    bool empty() const { return m_count == 0; }

    class iterator;
    iterator begin();
    iterator end();

    class const_iterator;
    const_iterator begin() const;
    const_iterator end() const;

private:
    size_t m_count = 0;
    struct Item;
    Item * m_head = nullptr;
    Item * m_tail = nullptr;

    void reverse(Item *& item);
};

template<class T>
struct List<T>::Item
{
    Item(T value, Item * next = nullptr) : value(value), next(next) {}
    T value;
    Item * next;
};

template<class T>
class List<T>::iterator
{
public:
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef int difference_type;
    iterator(iterator const & it) : m_it(it.m_it) {}
    iterator(List<T>::Item * item) : m_it(item) {}
    iterator operator++() { m_it = m_it->next; return *this; }
    iterator operator++(int) { iterator tmp; m_it = m_it->next; return tmp; }
    reference operator*() { return m_it->value; }
    pointer operator->()  { return m_it->value; }
    bool operator==(iterator const & it) { return m_it == it.m_it; }
    bool operator!=(iterator const & it) { return m_it != it.m_it; }
private:
    List<T>::Item * m_it;
};

template<class T>
void swap(List<T> & l, List<T> & r) noexcept
{
    std::swap(l.m_count, r.m_count);
    std::swap(l.m_head, r.m_head);
    std::swap(l.m_tail, r.m_tail);
}

template<class T>
List<T>::List() = default;

template <class T>
List<T>::List(const List & other)
{
    addList(other);
}

template<class T>
List<T>::List(std::initializer_list<T> args)
{
    for (auto const & arg : args)
        pushBack(arg);
}

template <class T>
List<T>::List::List(List && other) noexcept : List()
{
    swap(*this, other);
}

template <class T>
List<T> & List<T>::operator=(List other)
{
    if (this == &other)
        return *this;

    swap(*this, other);
    return *this;
}

template<class T>
List<T>::~List()
{
    Item * next = m_head;
    while(next)
    {
        auto cur = next;
        next = cur->next;
        delete cur;
        cur = nullptr;
    }
}

template<class T>
void List<T>::addList(const List & src)
{
    for (auto cur = src.m_head; cur != nullptr; cur = cur->next)
        pushBack(cur->value);
}

template<class T>
void List<T>::pushFront(T value)
{
    Item * item = new Item(value, m_head);
    if (m_head == nullptr)
        m_tail = item;

    m_head = item;
    ++m_count;
}

template <class T>
void List<T>::pushBack(T value)
{
    Item * item = new Item(value);
    if (m_tail == nullptr)
        m_head = item;
    else
        m_tail->next = item;

    m_tail = item;
    ++m_count;
}

template<class T>
T List<T>::popFront()
{
    int value = m_head->value;
    auto cur = m_head;
    m_head = m_head->next;
    delete cur;
    --m_count;

    return value;
}

template<class T>
T List<T>::popBack()
{
    int value = m_tail->value;
    Item * prev = nullptr;
    for (auto cur = m_head; cur != m_tail; cur = cur->next)
        prev = cur;

    prev->next = nullptr;
    delete m_tail;
    --m_count;
    m_tail = prev;

    return value;
}

template<class T>
bool List<T>::remove(T value)
{
    Item * prev = nullptr;
    Item * cur  = m_head;
    while(cur)
    {
        if (cur->value == value)
        {
            if (cur == m_head)
                m_head = m_head->next;
            else if (cur == m_tail)
            {
                m_tail = prev;
                m_tail->next = nullptr;
            }
            else if (prev)
                prev->next = cur->next;

            delete cur;
            cur = nullptr;
            --m_count;

            return true;
        }
        prev = cur;
        cur = cur->next;
    }

    return false;
}

template<class T>
void List<T>::insert(T value)
{
    Item * prev = nullptr;
    Item * cur = m_head;
    while (cur && cur->value < value)
    {
        prev = cur;
        cur = cur->next;
    }

    Item * item = new Item(value, cur);
    if (cur == nullptr)
        m_tail = item;
    if (prev == nullptr)
        m_head = item;
    else
        prev->next = item;
    ++m_count;
}

template<class T>
void List<T>::reverse()
{
    Item * cur = m_head;
    Item * prev = nullptr;
    while(cur)
    {
        Item * next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    m_tail = m_head;
    m_head = prev;
}

template<class T>
void List<T>::reverseUsingRecursion()
{
    m_tail = m_head;
    reverse(m_head);
}

template<class T>
void List<T>::reverse(Item *& item)
{
    if(!item)
        return;
    Item * first = item;
    Item * rest  = first->next;
    if(!rest)
        return;
    reverse(rest);
    first->next->next = first;
    first->next = nullptr;
    item = rest;
}

template<class T>
T & List<T>::front()
{
    return m_head->value;
}

template <class T>
const T & List<T>::front() const
{
    return m_head->value;
}

template<class T>
T & List<T>::back()
{
    return m_tail->value;
}

template<class T>
const T & List<T>::back() const
{
    return m_tail->value;
}

template<class T>
std::string List<T>::getAllItemsInfo() const
{
    std::stringstream stream;
    auto cur = m_head;
    while (cur)
    {
        stream << cur->value << ' ';
        cur = cur->next;
    }
    stream << std::endl;

    return stream.str();
}

template<class T>
typename List<T>::iterator List<T>::begin()
{
    return iterator(m_head);
}

template<class T>
typename List<T>::iterator List<T>::end()
{
    return iterator(m_tail->next);
}

}// end namespace
