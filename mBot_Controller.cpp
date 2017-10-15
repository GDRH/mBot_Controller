#include <SFML/Graphics.hpp>
#include <iostream>

#include "InputPlotter.h"
#include "SerialClass.h"

Serial * SP;

void processButtonPress( sf::Event::JoystickButtonEvent joystickButton ){
    char temp = joystickButton.button;
    if ( SP->IsConnected() ){
        switch( temp ){
            case 0:
                SP->WriteData("a",1);
                break;
            case 1:
                SP->WriteData("b",1);
                break;
            case 2:
                SP->WriteData("c",1);
                break;
            case 3:
                SP->WriteData("d",1);
                break;
            default:;
        }
        std::cout << "Sent data : " << char(temp+'a') << std::endl;
    }else{
        std::cout << "Serial Port not connected! Error" << std::endl;
    }
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

    SP = new Serial("\\\\.\\COM13");    // adjust as needed
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
