#ifndef SLIDER_H
#define SLIDER_H

#include <SFML/Config.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class Slider
{
    public:
        Slider( sf::Vector2f position, sf::Font * font, std::string name );

        void setValue( float value );
        void draw( sf::RenderWindow & window );

    protected:

    private:
        sf::RectangleShape background;
        sf::RectangleShape bar;
        sf::Text text;
};

#endif // SLIDER_H
