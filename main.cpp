#include <boost/bind.hpp>
#include "EventDef.h"
#include "EventManager.h"

 class UIClass
 {
 public:
     UIClass()
     {
     }
     
     ~UIClass()
     {
     }
     
    void RegistEvt()
    {
        REGIST_EVT((&EventManager::Instance()), EVT_TICK, TickEvent, UIClass, OnEvent);
    }
     int OnEvent(TickEvent *evt)
     {
         TickEvent *tickEvt = (TickEvent*)evt;
         printf("uiclass event, time now: %d, test_ =%d \n", (int)tickEvt->time_, tickEvt->test_);
         return 0;
     }
 };


int main(int argc, char* argv[])
{
    TickEvent tickEvt(20,25);
    UIClass ui;
    ui.RegistEvt();
    
    EventManager::Instance().DispatchEvent(&tickEvt);
    EventManager::Instance().ClearEventHandler(EVT_TICK);



}