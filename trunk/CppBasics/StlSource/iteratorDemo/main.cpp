#include <iostream>
#include <rope>
#include <memory>

using namespace std;

namespace yf
{
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
    ~List(){};
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
      os<<endl;
    }
  private:
    ListItem<T> * _front;
    ListItem<T> * _end;
    long size;
  };
}

int main()
{
  yf::List<int> a;
  a.insert_front(1);
  a.insert_front(2);
  a.insert_front(4);
  a.display();
}