#ifndef __MYLIST_H__
#define __MYLIST_H__
#include <iostream>

namespace yf {

  template<typename T> class List;

  template<typename T>
  class ListItem
  {
  public:
    friend class List<T>;
    T value() const {return _value;}
    ListItem * next() {return _next;}
  private:
    T _value;
    ListItem* _next;
  };


  template<typename T>
  class List
  {
  public:
    typedef ListItem<T>* ItemPointer;
    List():_front(NULL),_end(NULL),size(0){}
    ~List()
    {
      //没有清理内存
    };

    ItemPointer front() const {return _front;}

    void insert_front(const T& value)
    {
      if (_front == NULL && _end == NULL)
      {
        _front = new ListItem<T>();
        _front->_value = value;
        _front->_next = NULL;
        _end = _front;
      }
      else
      {
        ItemPointer tmp = new ListItem<T>();
        tmp->_value = value;
        tmp->_next = _front;
        _front = tmp;
      }
    }
    void insert_end(const T& value);
    void display(std::ostream &os = std::cout) const
    {
      for (ItemPointer p = _front;p != NULL;p = p->next())
      {
        os<<p->value()<<" ";
      }
      os<<std::endl;
    }
  private:
    ListItem<T> * _front;
    ListItem<T> * _end;
    long size;
  };



  template<typename Item>//Item是链表节点类型
  class ListIter
  {
    friend class ListIter<Item>;
  private:
    Item * ptr;
  public:
    ListIter(Item *p = NULL):ptr(p){}

    //操作符重载
    Item& operator*() const {return *ptr;}
    Item* operator->() const {return ptr;}
    //前加
    ListIter& operator++()
    {
      ptr = ptr->next();
      return *this;
    }
    //后加
    ListIter& operator++(int)
    {
      ListItem temp = &this;
      ++*this;
      return temp;
    }
    bool operator==(const ListIter& iter) const
    {
      return ptr == iter.ptr;
    }
    bool operator!=(const ListIter& iter) const
    {
      return ptr != iter.ptr;
    }
  };
} // yf

#endif // __MYLIST_H__
