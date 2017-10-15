#include <SFML/Graphics.hpp>
#include <iostream>

#include "InputPlotter.h"
#include "Serial.h"

Serial serial;

void processButtonPress( sf::Event::JoystickButtonEvent joystickButton ){
    char temp = joystickButton.button;
    serial.sendBytes( &temp, 1 );
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

    serial.init( "myfile.txt" );

    char temp;

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
