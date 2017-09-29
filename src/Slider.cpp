#include "Slider.h"

const float sliderW = 300.f, sliderH = 20.f, outline = 5.f;

Slider::Slider( sf::Vector2f position, sf::Font * font, std::string name ){
    background.setFillColor(sf::Color::White);
    background.setSize( sf::Vector2f ( sliderW + outline*2, sliderH + outline*2 ) );
    background.setPosition( position );

    bar.setFillColor(sf::Color(0,160,0));
    setValue(0);//Bar size

    position.x += outline; position.y += outline;
    bar.setPosition( position );

    text.setString( name );
    text.setFont( *font );
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(16);
    text.setOrigin( sf::Vector2f ( text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f ) );
    text.setPosition( background.getPosition() + bar.getSize() / 2.f );
}

void Slider::setValue(float value)
{
    float multiplier = (value+100.f)/200.f;
    bar.setSize( sf::Vector2f( sliderW*multiplier, sliderH ) );
}

void Slider::draw( sf::RenderWindow & window )
{
    window.draw(background);
    window.draw(bar);
    window.draw(text);
}
