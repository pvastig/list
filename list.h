#pragma once

#include <string>

namespace pa {

class List
{
public:
  List();
  List(const List & src);
  ~List();

  void addList    (const List & src);

  void push_front (int item);
  void push_back  (int item);

  int pop_front();
  int pop_back();

  bool remove     (int value);
  void insert     (int value);
  void reverse();

  int & front();
  const int & front() const;

  int & back();
  const int & back() const;

  size_t size() const { return m_count; }
  std::string getAllItemsInfo() const;

private:
  struct Item
  {
    int value;
    Item * next;
    Item(int value, Item * next = nullptr) : value(value), next(next) {}
  };

  size_t m_count = 0;
  Item * m_head = nullptr;
  Item * m_tail = nullptr;
};

}// end namespace
