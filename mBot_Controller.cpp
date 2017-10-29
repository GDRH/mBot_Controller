#include <SFML/Graphics.hpp>
#include <iostream>

#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "hidapi.h"

// Headers needed for sleeping.
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#define MAX_STR 255

#include "InputPlotter.h"

hid_device *handle; // Device handler for the USB Stick

//unsigned char cmd_ff[] = "\x00\x0a\xff\x55\x07\x00\x02\x05\x01\xff\xff\x00";
    //cmd_ff[0] = 0;  // Default zero
    //cmd_ff[1] = 10; // Length of command
    // ff 55 07 00 02 05 01 ff ff 00

unsigned char bufferM1Go[]  =  "\x00\x09\xff\x55\x06\x00\x02\x0a\x0a\xff\x00";
unsigned char bufferM2Go[]  =  "\x00\x09\xff\x55\x06\x00\x02\x0a\x09\x01\xff";

unsigned char buffFwrd[] = "\x00\x0a\xff\x55\x07\x00\x02\x05\x01\xff\xff\x00";
unsigned char buffRight[] = "\x00\x0a\xff\x55\x07\x00\x02\x05\x01\xff\x01\xff";
unsigned char buffLeft[]= "\x00\x0a\xff\x55\x07\x00\x02\x05\xff\x00\xff\x00";
unsigned char buffBack[]= "\x00\x0a\xff\x55\x07\x00\x02\x05\xff\x00\x01\xff";
/*ff 55 07 00 02 05 ff 00 01 ff - Inapoi

ff 55 07 00 02 05 01 ff 01 ff - Right
ff 55 07 00 02 05 ff 00 ff 00 - Left*/

unsigned char bufferM1Stop[] = "\x00\x09\xff\x55\x06\x00\x02\x0a\x09\x00\x00";
unsigned char bufferM2Stop[] = "\x00\x09\xff\x55\x06\x00\x02\x0a\x0a\x00\x00";

unsigned char bufStop[] = "\x00\x0a\xff\x55\x07\x00\x02\x05\x00\x00\x00\x00 ";

unsigned char bufferM1Back[] = "\x00\x09\xff\x55\x06\x00\x02\x0a\x09\xff\x00";
unsigned char bufferM2Back[] = "\x00\x09\xff\x55\x06\x00\x02\x0a\x0a\x01\xff";

/*
M2 inapoi :  ff 55 06 00 02 0a 0a 01 ff
M1 inapoi :  ff 55 06 00 02 0a 09 ff 00
M2 stop :    ff 55 06 00 02 0a 0a 00 00
M2 inainte : ff 55 06 00 02 0a 0a ff 00
M1 stop :    ff 55 06 00 02 0a 09 00 00
M1 inainte : ff 55 06 00 02 0a 09 01 ff
*/

void processButtonPress( sf::Event::JoystickButtonEvent joystickButton ){
    char temp = joystickButton.button;
    int res;

    switch( temp ){
        case 0:
            //Go forward
            res = hid_write(handle, buffFwrd, 12);// Send command to mBot
            break;
        case 1:
            //Right
            res = hid_write(handle, buffRight, 12);
            break;
        case 2:
            //Go back
            res = hid_write(handle, buffBack, 12);
            break;
        case 3:
            //Left
            res = hid_write(handle, buffLeft, 12);
            break;
        /* -- AICI SE MAI POT ADAUGA ACTIUNI PENTRU BUTOANE...
        case 3:
            break;
        */
        default:;
    }
    if (res < 0) {
        printf("Unable to write()\n");
        printf("Error: %ls\n", hid_error(handle));
    }
}

void processButtonRelease( sf::Event::JoystickButtonEvent joystickButton ){
    int res;
    res = hid_write(handle, bufStop, 12);
}

void processAxisMove( sf::Event::JoystickMoveEvent joystickButton ){

}

int main()
{
    sf::RenderWindow window( sf::VideoMode(800, 600), "mBot Controller v0.1" );

    for ( int i = 0; i < 4; i++ )
        if (sf::Joystick::isConnected(i))
            std::cout << "Joystick " << i << " connected : " << sf::Joystick::getIdentification(i).name.toAnsiString();

    sf::Font ubuntuFont;
    ubuntuFont.loadFromFile("Ubuntu-R.ttf");

    InputPlotter plotter(0,&ubuntuFont);

    //////////////////////////HID_API STUFF/////////////////////////////
    int res;
    unsigned char buf[256];

    wchar_t wstr[MAX_STR];
    int i;

    struct hid_device_info *devs, *cur_dev;

    if (hid_init()){
        printf("Failed to init HID!");
        return -1;
    }

    // Open device
    handle = hid_open(0x0416, 0xffff, NULL);
    if (!handle) {
        printf("Unable to open device\n");
         return 1;
    } else {
        printf("Device open\n");
    }

    // Optional Read the Manufacturer String
    wstr[0] = 0x0000;
    res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
    if (res < 0)
        printf("Unable to read manufacturer string\n");
    printf("Manufacturer String: %ls\n", wstr);

    //////////////////////////HID_API STUFF/////////////////////////////

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch( event.type ){
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::JoystickButtonPressed:
                    plotter.update( event.joystickButton, true );
                    processButtonPress( event.joystickButton );
                    break;

                case sf::Event::JoystickButtonReleased:
                    plotter.update( event.joystickButton, false );
                    processButtonRelease( event.joystickButton );
                    break;

                case sf::Event::JoystickMoved:
                    plotter.update( event.joystickMove );
                    processAxisMove( event.joystickMove );
                    break;
                default:;
            }
        }

        window.clear();
        plotter.draw(window);
        window.display();
    }

    hid_close(handle);

    /* Free static HIDAPI objects. */
    hid_exit();

    return 0;
}
