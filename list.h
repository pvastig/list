#pragma once

#include <initializer_list>
#include <iostream>
#include <sstream>
#include <string>
#include <cassert>

namespace pa {

template<class T>
class List
{
    template<T const &> //TODO: issue https://stackoverflow.com/questions/2183087/why-cant-i-use-float-value-as-a-template-parameter
    friend void swap(List<T> & l, List<T> & r) noexcept;
public:
    List();
    explicit List(std::initializer_list<T> args);
    List(List const & other);
    List(List && other) noexcept;
    List & operator=(List other);
    ~List();

    void addList(List const & other);

    void pushFront(T value);
    void pushBack (T value);

    T popFront();
    T popBack ();

    bool remove(T value);
    void insert(T value);

    void reverse();
    void reverseUsingRecursion();

    T & front();
    T const & front() const;

    T & back();
    T const & back() const;

    size_t size() const { return m_count; }
    std::string getAllItemsInfo() const;

    bool empty() const { return m_count == 0; }

    template<class Type,
             class UnqualifiedType = std::remove_cv_t<Type>>
    class ForwardIterator : public std::iterator<std::forward_iterator_tag,
                                                 UnqualifiedType,
                                                 std::ptrdiff_t,
                                                 Type*,
                                                 Type&>
    {
        friend class List<UnqualifiedType>;
        typename List<UnqualifiedType>::Node * m_it;

        explicit ForwardIterator(typename List<UnqualifiedType>::Node * it)
            : m_it(it)
        {
        }

    public:
        ForwardIterator() : m_it(nullptr)
        {
        }

        void swap(ForwardIterator & other) noexcept
        {
            using std::swap;
            swap(m_it, other.iter);
        }

        ForwardIterator& operator++()
        {
            assert(m_it != nullptr && "Out-of-bounds iterator increment!");
            m_it = m_it->next;
            return *this;
        }

        ForwardIterator operator++(int)
        {
            assert(m_it != nullptr && "Out-of-bounds iterator increment!");
            ForwardIterator tmp(*this);
            m_it = m_it->next;
            return tmp;
        }

        // two-way comparison: v.begin() == v.cbegin() and vice versa
        template<class OtherType>
        bool operator==(ForwardIterator<OtherType> const & rhs) const
        {
            return m_it == rhs.m_it;
        }

        template<class OtherType>
        bool operator != (ForwardIterator<OtherType> const & rhs) const
        {
            return m_it != rhs.m_it;
        }

        Type & operator*() const
        {
            assert(m_it != nullptr && "Invalid iterator dereference!");
            return m_it->value;
        }

        Type & operator->() const
        {
            assert(m_it != nullptr && "Invalid iterator dereference!");
            return m_it->value;
        }

        // One way conversion: iterator -> const_iterator
        operator ForwardIterator<const Type>() const
        {
            return ForwardIterator<const Type>(m_it);
        }
    };

    using iterator = ForwardIterator<T>;
    using const_iterator = ForwardIterator<const T>;

    iterator begin();
    iterator end();

    const_iterator cbegin() const;
    const_iterator cend() const;

private:
    size_t m_count = 0;
    struct Node;
    Node * m_head = nullptr;
    Node * m_tail = nullptr;

    void reverse(Node *& item);
};

template<class T>
struct List<T>::Node
{
    Node(T value, Node * next = nullptr) : value(value), next(next) {}
    T value;
    Node * next;
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
List<T>::List(List const & other)
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
    using std::swap;
    swap(*this, other);
}

template <class T>
List<T> & List<T>::operator=(List other)
{
    using std::swap;
    if (this == &other)
        return *this;

    swap(*this, other);
    return *this;
}

template<class T>
List<T>::~List()
{
    Node * next = m_head;
    while(next)
    {
        Node * cur = next;
        next = cur->next;
        delete cur;
        cur = nullptr;
    }
}

template<class T>
void List<T>::addList(List const & other)
{
    for (auto const & item : other)
        pushBack(item->value);
}

template<class T>
void List<T>::pushFront(T value)
{
    Node * item = new Node(value, m_head);
    if (m_head == nullptr)
        m_tail = item;

    m_head = item;
    ++m_count;
}

template <class T>
void List<T>::pushBack(T value)
{
    Node * item = new Node(value);
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
    T value = m_head->value;
    Node * cur = m_head;
    m_head = m_head->next;
    delete cur;
    --m_count;

    return value;
}

template<class T>
T List<T>::popBack()
{
    T value = m_tail->value;
    Node * prev = nullptr;
    for (Node * cur = m_head; cur != m_tail; cur = cur->next)
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
std::string List<T>::getAllItemsInfo() const
{
    std::stringstream stream;
    Node * cur = m_head;
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

template<class T>
typename List<T>::const_iterator List<T>::cbegin() const
{
    return const_iterator(begin());
}

template<class T>
typename List<T>::const_iterator List<T>::cend() const
{
    return const_iterator(end());
}

}// end namespace
