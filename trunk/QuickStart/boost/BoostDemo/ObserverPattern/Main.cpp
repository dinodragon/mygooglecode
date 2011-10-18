//观察者模式

#include <iostream>
#include <list>
#include <boost/shared_ptr.hpp>
using namespace std;
using namespace boost;

class Observer
{
public:
  virtual void updata(float temperature, float humidity, float pressure) = 0;
};

class Average : public Observer 
{
public: 
  void updata(float temperature, float humidity, float pressure)
  { 
    cout << (temperature+humidity+pressure)/3 <<endl; 
  }
};

class Min : public Observer
{ 
public: 
  void updata(float temperature, float humidity, float pressure)
  { 
    float tmp = min(temperature,humidity); 
    tmp = min(tmp, pressure);

    cout << tmp <<endl; 
  } 
};

class Max : public Observer 
{ 
  void updata(float temperature, float humidity, float pressure) 
  { 
    float tmp = max(temperature,humidity); 
    tmp = max(tmp, pressure);
    cout << tmp <<endl; 
  } 
};

class SubjectBase 
{ 
public: 
  virtual void registerObject(shared_ptr<Observer> observer) = 0; 
  virtual void removeObject(shared_ptr<Observer> observer) = 0; 
  virtual void notifyObject() = 0; 
};

class WeatherData : public SubjectBase 
{ 
public: 
  explicit WeatherData(float temperature, float humidity, float pressure) 
  { 
    temperature_    = temperature; 
    humidity_        = humidity; 
    pressure_        = pressure; 
  }

  void registerObject(shared_ptr<Observer> observer) 
  { 
    observersList_.push_back(observer); 
  }

  void removeObject(shared_ptr<Observer> observer) 
  { 
    observersList_.remove(observer); 
  }

  void notifyObject() 
  { 
    for (list<shared_ptr<Observer>>::iterator pos = observersList_.begin(); 
      pos != observersList_.end(); ++pos) 
    { 
      (*pos)->updata(temperature_, humidity_, pressure_); 
    } 
  }

private: 
  list<shared_ptr<Observer>>    observersList_; 
  float                        temperature_; 
  float                        humidity_; 
  float                        pressure_; 
};

int main(int argc, char* argv[]) 
{ 
  shared_ptr<Observer> observer_1(new Average()); 
  shared_ptr<Observer> observer_2(new Min()); 
  shared_ptr<Observer> observer_3(new Max()); 

  shared_ptr<SubjectBase> subject(new WeatherData(100, 110, 120)); 
  subject->registerObject(observer_1); 
  subject->registerObject(observer_2); 
  subject->registerObject(observer_3); 
  subject->notifyObject();

  return 0; 
}
