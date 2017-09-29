#include "InputPlotter.h"

const float xOffset = 10, yOffset = 10;

InputPlotter::InputPlotter( unsigned int _id, sf::Font* _font )
{
    id = _id;
    font = _font;

    char sliderName[7] = "AXIS x";
    for ( int i = 0; i < 8; i++ ){
        sliderName[5] = '0'+i;
        sliders[i] = new Slider( sf::Vector2f( xOffset, yOffset+i*40 ), _font, sliderName );
    }

    char buttonName[2] = "x";
    for ( int i = 0; i < 10; i++ ){
        buttonName[0] = '0'+i;
        buttons[i] = new Button( sf::Vector2f( xOffset + (i%5)*50, yOffset+350+(i/5)*50 ), _font, buttonName );
    }
}

void InputPlotter::update(sf::Event::JoystickButtonEvent event, bool pressed )
{
    if ( event.joystickId != id )
        return;

    buttons[event.button]->setValue(pressed);
}

void InputPlotter::update(sf::Event::JoystickMoveEvent event)
{
    if ( event.joystickId != id )
        return;

    sliders[event.axis]->setValue( event.position );
}

void InputPlotter::draw(sf::RenderWindow& window)
{
    for ( int i = 0; i < 8; i++ ){
        sliders[i]->draw(window);
    }
    for ( int i = 0; i < 10; i++ ){
        buttons[i]->draw(window);
    }
}
