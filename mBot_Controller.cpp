#include <SFML/Graphics.hpp>
#include <iostream>

#include "InputPlotter.h"
#include "SerialClass.h"

Serial * SP;

char bufferM1Go[] = "\xff\x55\x06\x00\x02\x0a\x0a\xff\x00";
char bufferM2Go[] = "\xff\x55\x06\x00\x02\x0a\x09\x01\xff";

char bufferM1Stop[] = { (char)0xff, (char)0x55, (char)0x06, (char)0x00, (char)0x02, (char)0x0a, (char)0x09, (char)0x00, (char)0x00 };
char bufferM2Stop[] = { (char)0xff, (char)0x55, (char)0x06, (char)0x00, (char)0x02, (char)0x0a, (char)0x0a, (char)0x00, (char)0x00 };

char bufferM1Back[] = "\xff\x55\x06\x00\x02\x0a\x0a\x01\xff";
char bufferM2Back[] = "\xff\x55\x06\x00\x02\x0a\x09\xff\x00";

void processButtonPress( sf::Event::JoystickButtonEvent joystickButton ){
    char temp = joystickButton.button;
    if ( SP->IsConnected() ){
        switch( temp ){
            case 0:
                SP->WriteData( bufferM1Go, 9 );
                SP->WriteData( bufferM2Go, 9 );
                break;
            case 1:
                SP->WriteData( bufferM1Stop, 9 );
                SP->WriteData( bufferM2Stop, 9 );
                break;
            case 2:
                SP->WriteData( bufferM2Back, 9 );
                SP->WriteData( bufferM1Back, 9 );
                break;
            /*
            case 3:
                SP->WriteData("d",1);
                break;
            */
            default:;
        }
        std::cout << "Sent data : " << char(temp+'a') << std::endl;
    }else{
        std::cout << "Serial Port not connected! Error" << std::endl;
    }

    /*
    M2 inapoi : ff 55 06 00 02 0a 0a 01 ff
    M1 inapoi : ff 55 06 00 02 0a 09 ff 00
    M2 stop : ff 55 06 00 02 0a 0a 00 00
    M2 inainte : ff 55 06 00 02 0a 0a ff 00
    M1 stop : ff 55 06 00 02 0a 09 00 00
    M1 inainte : ff 55 06 00 02 0a 09 01 ff
    */
}

void processButtonRelease( sf::Event::JoystickButtonEvent joystickButton ){

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

    SP = new Serial("\\\\.\\COM5");    // adjust as needed
	if (SP->IsConnected())
		std::cout << "Arduino connected" << std::endl;

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

    return 0;
}
