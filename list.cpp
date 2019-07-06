#include "list.h"

#include <cassert>
#include <iostream>
#include <sstream>

namespace pa {

List::List() =default;

List::List(const List & src)
{
    addList(src);
}

List::~List()
{
    auto cur = m_head;
    while(cur)
    {
        Item * next = cur->next;
        delete cur;
        cur = nullptr;
        cur = next;
    }
}

void List::addList(const List & src)
{ 
    for (auto cur = src.m_head; cur != nullptr; cur = cur->next)
        pushBack(cur->value);
}

void List::pushFront(int value)
{
    auto item = new Item(value, m_head);
    if (m_head == nullptr)
        m_tail = item;

    m_head = item;
    ++m_count;
}

void List::pushBack(int value)
{
    auto item = new Item(value);
    if (m_tail == nullptr)
        m_head = item;
    else
        m_tail->next = item;

    m_tail = item;
    ++m_count;
}

int List::popFront()
{
    if (m_count == 0)
        return 0;
    int res = m_head->value;
    m_head = m_head->next;
    --m_count;

    return res;
}

int List::popBack()
{
    if (m_count == 0)
        return 0;

    int res = m_tail->value;
    Item * pPrev = nullptr;
    for (Item * pCur = m_head; pCur != m_tail; pCur = pCur->next)
        pPrev = pCur;

    pPrev->next = nullptr;
    delete m_tail;
    --m_count;
    m_tail = pPrev;

    return res;
}

bool List::remove(int value)
{
    Item * pPrev = nullptr;
    Item * pCurrent = m_head;
    while(pCurrent)
    {
        if (pCurrent->value == value)
        {
            if (nullptr == pPrev)
                m_head = m_head->next;
            else if (pCurrent == m_tail)
                m_tail = pCurrent;
            else if (pPrev)
                pPrev->next = pCurrent->next;

            delete pCurrent;
            --m_count;

            return true;
        }
        else
        {
            pPrev = pCurrent;
            pCurrent = pCurrent->next;
        }
    }

    return false;
}

void List::insert(const int value)
{
    Item * pPrev = nullptr;
    Item * pCur = m_head;
    while (pCur != nullptr && pCur->value < value)
    {
        pPrev = pCur;
        pCur = pCur->next;
    }

    auto pItem = new Item(value, pCur);
    if (nullptr == pCur)
        m_tail = pItem;

    if (pPrev == nullptr)
        m_head = pItem;
    else
        pPrev->next = pItem;

    m_count++;
}

void List::reverse()
{
    Item * pCurrent = m_head;
    Item * pPrev = nullptr;
    while(pCurrent != nullptr)
    {
        Item * pNext = pCurrent->next;
        pCurrent->next = pPrev;
        pPrev = pCurrent;
        pCurrent = pNext;
    }

    m_tail = m_head;
    m_head = pPrev;
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
