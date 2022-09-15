#include "Listener.h"

Listener::Listener(Button *modebutton, Button *powerbutton, Controller *control, ClockCheck *clock)
{
    this -> modeButton  = modebutton;
    this -> powerButton = powerbutton;
    controller = control;
    clockCheck = clock;
}

Listener::~Listener()
{
}

void Listener::checkEvent()
{
    if (modeButton->getState() == RELEASE_ACTIVE)
    {
        controller->updateEvent("modeButton");
    }

    if (powerButton->getState() == RELEASE_ACTIVE)
    {
        controller->updateEvent("powerButton");
    }

    //1초가 되면 이벤트 발생 -> controller로 넘어줌
    if (clockCheck -> isUpdate())
    {
        controller -> updateEvent("clockUpdate");
    }
}