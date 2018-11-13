#ifndef EVENT_H
#define EVENT_H
#include <boost/smart_ptr.hpp>
#include <boost/function.hpp>

struct Event
{
    Event(int id) : id_(id)
    {}
    ~Event()
    {}
    int id_;
};

class EventHandler
{
public:
    virtual int HandleEvent(Event *evt) = 0;
};

template<class T>
class ClassEventHandler : public EventHandler
{

public:
    ClassEventHandler(boost::function<int (T*)>& func): func_(func){}

    virtual int HandleEvent(Event *evt)
    {
        T* realEvt = static_cast<T*>(evt);
        if(func_)
            return func_(realEvt);
        return 0;
    }

private:
    boost::function<int (T*)> func_;
};

typedef boost::shared_ptr<EventHandler> EventHandlerPtr;

#endif