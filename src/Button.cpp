#include "Button.h"

const float ButtonW = 30.f, ButtonH = 30.f, outline = 5.f;

Button::Button( sf::Vector2f position, sf::Font * font, std::string name ){
    background.setFillColor(sf::Color::White);
    background.setSize( sf::Vector2f ( ButtonW + outline*2, ButtonH + outline*2 ) );
    background.setPosition( position );

    box.setFillColor(sf::Color(0,160,0));
    setValue(false);//box size

    position.x += outline; position.y += outline;
    box.setPosition( position );

    text.setString( name );
    text.setFont( *font );
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(16);
    text.setOrigin( sf::Vector2f ( text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f ) );
    text.setPosition( box.getPosition() + box.getSize() / 2.f );
}

void Button::setValue( bool value ){
    box.setSize( sf::Vector2f ( ButtonW, ButtonH ) );
    box.setPosition( background.getPosition() + sf::Vector2f( outline, outline ) );
    state = value;
}

void Button::draw( sf::RenderWindow & window )
{
    window.draw(background);
    if ( state )
        window.draw(box);
    window.draw(text);
}
