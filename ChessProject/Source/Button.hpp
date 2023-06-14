#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

class Button
{
protected:
    sf::Text buttonName;
    sf::RectangleShape button;

public:
    // Button::Button();
    // Button::Button(std::string str, sf::Vector2f size, int fontSize, sf::Color bgColor, sf::Color textColor);
    void setFont(sf::Font &font);
    void setTextSize(unsigned int size);
    void setTextColor(sf::Color color);
    void setTitle(std::string str);
    void setBackgroundColor(sf::Color color);
    void setPosition(float x, float y);
    void setSize(float width, float height);
    void setScale(float w, float h);
    void setTexture(sf::Texture &texture);
    int getLocalBoundsWidth();
    int getLocalBoundsHeight();
    int getPositionX();
    int getPositionY();
    int getSizeWidth();
    int getSizeHeight();
    void drawTo(sf::RenderWindow &window);
    bool isMouseOver(sf::RenderWindow &window);
    void setOriginToCenter();
    void setOriginToCenterForText();
};
