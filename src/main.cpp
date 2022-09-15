#include <iostream>
#include <wiringPi.h>
#include <time.h>
#include "Button.h"
#include "Led.h"
#include "Listener.h"
#include "Controller.h"
#include "View.h"
#include "Service.h"
#include "LCD.h"
#include "ClockView.h"
#include "ClockService.h"
#include "ClockCheck.h"
#include "DHT11.h"

int main()
{
    std::cout << "Hello World!" << std::endl;
    
    Button modeButton(27);
    Button powerButton(28);

    ClockCheck clockCheck;

    Led led1(21);
    Led led2(22);
    Led led3(23);
    Led led4(24);
    Led led5(25);

    LCD lcd(new I2C("/dev/i2c-1", 0x27));

    DHT11 dht(7);
    DHT_Data dhtData;

    View view(&led1, &led2, &led3, &led4, &led5, &lcd);
    ClockView clockView(&lcd);

    Service service(&view);
    ClockService clockService(&clockView);
    Controller control(&service, &clockService);
    Listener listener(&modeButton, &powerButton, &control, &clockCheck);
    
    while (1)
    {
        listener.checkEvent();
        view.lightView();
        delay(50);

        dhtData = dht.readData();
        if (!dhtData.error) {
            std::printf("RH: %d.%d, Temp: %d.%d\n", 
                        dhtData.RH, dhtData.RHDec,
                        dhtData.Temp, dhtData.TempDec);
        }
        delay(3000);
    }

    return 0;
}