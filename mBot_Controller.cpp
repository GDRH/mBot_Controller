#include <SFML/Graphics.hpp>
#include <iostream>

#include "InputPlotter.h"

int main()
{
    sf::RenderWindow window( sf::VideoMode(800, 600), "mBot Controller v0.1" );

    for ( int i = 0; i < 4; i++ )
        if (sf::Joystick::isConnected(i))
            std::cout << "Joystick " << i << " connected : " << sf::Joystick::getIdentification(i).name.toAnsiString();

    sf::Font ubuntuFont;
    ubuntuFont.loadFromFile("Ubuntu-R.ttf");

    InputPlotter plotter(0,&ubuntuFont);

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
                    plotter.update(event.joystickButton, true);
                    break;

                case sf::Event::JoystickButtonReleased:
                    plotter.update(event.joystickButton, false);
                    break;

                case sf::Event::JoystickMoved:
                    plotter.update(event.joystickMove);
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
