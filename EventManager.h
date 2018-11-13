#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include <stdio.h>
#include <iostream>
#include <list>
#include <map>
#include "Event.h"

using namespace std;

#define REGIST_EVT(evt_mgr, evt_id, evt, cls, func)    \
    boost::function<int (evt *)>  f =     \
        boost::bind(static_cast<int (cls::*)(evt*)>(&cls::func), this, _1);    \
    evt_mgr->AddEventHandler(evt_id, f);


class EventManager
{
public:
    typedef std::list<EventHandlerPtr> HandlerList;
    typedef std::map<int, HandlerList> IdHandlerMap;

    
public:
    static EventManager &Instance()
    {
        static EventManager inst_;
        return inst_;
    }
    
    
    template<class T>
    void AddEventHandler(int id, boost::function<int (T *)>&  func)
    {
        if (func == NULL)
            return;
        
        pair<IdHandlerMap::iterator,bool> pair = handler_map_.insert(std::make_pair(id, HandlerList()));
        IdHandlerMap::iterator it = pair.first;
        if (it == handler_map_.end())
            return;
        EventHandlerPtr handler_ptr = (EventHandlerPtr)new ClassEventHandler<T>(func);
        it->second.push_back(handler_ptr);
    }
    
    template<class T>
    void DispatchEvent(T *evt)
    {
         if (NULL == evt) {
            return;
        }

        IdHandlerMap::iterator it = handler_map_.find(evt->id_);
        if (it == handler_map_.end())
            return;
        HandlerList &handler_list = it->second;
        HandlerList::iterator listIt = handler_list.begin();
        for (; listIt != handler_list.end(); ++listIt)
        {
            if ((*listIt) == NULL) continue;
            (*listIt)->HandleEvent(evt);
        }
    }


    void ClearEventHandler(int id)
    {
        handler_map_.erase(id);
    }
   
private:
    EventManager(){}
    EventManager(const EventManager&){}
    ~EventManager(){}

    IdHandlerMap handler_map_;
};


#endif