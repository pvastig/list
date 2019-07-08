#include "list.h"

#include <utility>
#include <cassert>
#include <iostream>
#include <sstream>

namespace pa {

void swap(pa::List & l, pa::List & r) noexcept
{
    std::swap(l.m_count, r.m_count);
    std::swap(l.m_head, r.m_head);
    std::swap(l.m_tail, r.m_tail);
}

List::List() =default;

List::List(const List & other)
{
    addList(other);
}

List::List(List && other) : List()
{
    swap(*this, other);
}

List & List::operator=(List other)
{
    if (this == &other)
        return *this;

    swap(*this, other);
    return *this;
}

List::~List()
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

void List::addList(const List & src)
{ 
    for (auto cur = src.m_head; cur != nullptr; cur = cur->next)
        pushBack(cur->value);
}

void List::pushFront(int value)
{
    Item * item = new Item(value, m_head);
    if (m_head == nullptr)
        m_tail = item;

    m_head = item;
    ++m_count;
}

void List::pushBack(int value)
{
    Item * item = new Item(value);
    if (m_tail == nullptr)
        m_head = item;
    else
        m_tail->next = item;

    m_tail = item;
    ++m_count;
}

int List::popFront()
{
    int value = m_head->value;
    auto cur = m_head;
    m_head = m_head->next;
    delete cur;
    --m_count;

    return value;
}

int List::popBack()
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

bool List::remove(int value)
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

void List::insert(int value)
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

void List::reverse()
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

void List::reverseUsingRecursion()
{
    m_tail = m_head;
    reverse(m_head);
}

void List::reverse(Item *& item)
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

int & List::front()
{
    return m_head->value;
}

const int & List::front() const
{
    return m_head->value;
}

int & List::back()
{
    return m_tail->value;
}

const int & List::back() const
{
    return m_tail->value;
}

std::string List::getAllItemsInfo() const
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

}//end namepace pa

