#pragma once

#include <cassert>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

namespace pa {

template<class T>
class List;

template <class T>
std::ostream& operator<<(std::ostream &, List<T> const&);

template<class T>
class List
{
    friend std::ostream& operator<< <T>(std::ostream& os, List const& list);

public:
    List();
    explicit List(std::initializer_list<T> args);
    explicit List(T value);
    List(const List& other);
    List(List&& other) noexcept;
    List& operator=(List other);
    ~List();

    void addList(List const & other);

    //TODO: T const& value?
    void pushFront(T value);
    //TODO: implement emplaceFront(T value);
    void pushBack (T value);
    //TODO: implement void emplaceBack(T value);

    T popFront();
    T popBack ();

    bool remove(T value);
    void insert(T value);

    void reverse();
    //TODO: rename method
    void reverseUsingRecursion();

    T& front();
    T const& front() const;

    T& back();
    T const& back() const;

    size_t size() const { return m_count; }

    bool empty() const { return m_count == 0; }

    //bool erase(iterator it);
    void clear();

private:
    void swap(List& other) noexcept;

    size_t m_count = 0;

	struct Node;
    Node* m_head = nullptr;
    Node* m_tail = nullptr;

    void reverse(Node*& item);
    std::string printItems() const;
};

template<class T>
struct List<T>::Node
{
    Node(T value, Node* next = nullptr) : value(value), next(next) {}
    T value;
    Node* next;
};

template<class T>
void List<T>::swap(List& other) noexcept
{
    std::swap(m_count, other.m_count);
    std::swap(m_head, other.m_head);
    std::swap(m_tail, other.m_tail);
}

template<class T>
std::ostream& operator<<(std::ostream& os, List<T> const& list)
{
    return os << list.printItems();
}

template<class T>
List<T>::List() = default;

template<class T>
List<T>::List(T value) : List({value})
{
}

template <class T>
List<T>::List(List const& other)
{
    addList(other);
}

template<class T>
List<T>::List(std::initializer_list<T> args)
{
    for (auto const& arg : args)
    {
        pushBack(arg);
    }
}

template <class T>
List<T>::List(List&& other) noexcept : List()
{
    swap(*this, other);
}

template <class T>
List<T>& List<T>::operator=(List other)
{
    if (this == &other)
    {
        return *this;
    }

    swap(*this, other);
    return *this;
}

template<class T>
List<T>::~List()
{
    clear();
}

template<class T>
void List<T>::addList(List const& other)
{
    for (auto const& item : other)
    {
        pushBack(item->value);
    }
}

template<class T>
void List<T>::pushFront(T value)
{
    Node* item = new Node(value, m_head);
    if (m_head == nullptr)
    {
        m_tail = item;
    }

    m_head = item;
    ++m_count;
}

template <class T>
void List<T>::pushBack(T value)
{
    Node* item = new Node(value);
    if (m_tail == nullptr)
    {
        m_head = item;
    }
    else
    {
        m_tail->next = item;
    }

    m_tail = item;
    ++m_count;
}

template<class T>
T List<T>::popFront()
{
    assert(!empty());
    auto value = m_head->value;
    Node* cur = m_head;
	m_head = m_head->next;
    delete cur;

    if (m_count == 1)
    {
        m_tail = nullptr;
    }
    --m_count;

    return value;
}

template<class T>
T List<T>::popBack()
{
    assert(!empty());
    auto value = m_tail->value;
    Node * prev = nullptr;
    for (Node * cur = m_head; cur != m_tail; cur = cur->next)
        prev = cur;

    if (m_count == 1)
        m_head = prev;
    else
        prev->next = nullptr;
    delete m_tail;
    --m_count;
    m_tail = prev;

    return value;
}

template<class T>
bool List<T>::remove(T value)
{
    Node * prev = nullptr;
    Node * cur  = m_head;
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
    Node * prev = nullptr;
    Node * cur = m_head;
    while (cur && cur->value < value)
    {
        prev = cur;
        cur = cur->next;
    }

    Node * item = new Node(value, cur);
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
    Node * cur = m_head;
    Node * prev = nullptr;
    while(cur)
    {
        Node * next = cur->next;
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
void List<T>::reverse(Node *& item)
{
    if(!item)
        return;
    Node * first = item;
    Node * rest  = first->next;
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
T const & List<T>::front() const
{
    return m_head->value;
}

template<class T>
T & List<T>::back()
{
    return m_tail->value;
}

template<class T>
T const & List<T>::back() const
{
    return m_tail->value;
}

template<class T>
std::string List<T>::printItems() const
{
    if (empty())
        return std::string();
    std::stringstream stream;
    for (auto const & it : *this)
        stream << it << ' ';
    stream << std::endl;

    return stream.str();
}

//TODO: improve clear using iterators
template<class T>
void List<T>::clear()
{
    Node * next = m_head;
    while(next)
    {
        Node * cur = next;
        next = cur->next;
        delete cur;
        cur = nullptr;
        --m_count;
    }
    m_tail = m_head = nullptr;
    assert(m_count == 0);
}

}// end namespace
