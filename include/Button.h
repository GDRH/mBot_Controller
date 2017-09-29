#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Config.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class Button
{
    public:
        Button( sf::Vector2f position, sf::Font * font, std::string name );

        void setValue( bool value );
        void draw( sf::RenderWindow & window );

    protected:

    private:
        sf::RectangleShape background;
        sf::RectangleShape box;
        bool state;
        sf::Text text;
};

#endif // BUTTON_H
