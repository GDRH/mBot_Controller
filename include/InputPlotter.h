#ifndef INPUTPLOTTER_H
#define INPUTPLOTTER_H

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Font.hpp>

#include "Slider.h"
#include "Button.h"

class InputPlotter
{
    public:
        InputPlotter( unsigned int id, sf::Font * font );
        //virtual ~InputPlotter();

        void update( sf::Event::JoystickButtonEvent event, bool pressed );
        void update( sf::Event::JoystickMoveEvent event );

        void draw( sf::RenderWindow & window );
    protected:

    private:
        unsigned int id;
        sf::Font * font;

        Slider * sliders[8];
        Button * buttons[10];
};

#endif // INPUTPLOTTER_H
