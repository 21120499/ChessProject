#include "Button.hpp"

/* Button::Button()
{
    buttonName.setString("Button");
} */

/* Button::Button(std::string str, sf::Vector2f size, int fontSize, sf::Color bgColor, sf::Color textColor)
{
    button.setFillColor(bgColor);
    button.setSize(size);

    buttonName.setString(str);
    buttonName.setFillColor(textColor);
    buttonName.setCharacterSize(fontSize);
} */

void Button::setFont(sf::Font &font)
{
    buttonName.setFont(font);
}

void Button::setTextSize(unsigned int size)
{
    buttonName.setCharacterSize(size);
}

void Button::setTextColor(sf::Color color)
{
    buttonName.setFillColor(color);
}

void Button::setTitle(std::string str)
{
    buttonName.setString(str);
}

void Button::setBackgroundColor(sf::Color color)
{
    button.setFillColor(color);
}

void Button::setPosition(float x, float y)
{

    // if you want to this alignment center text work,
    // set string for text first
    this->setOriginToCenter();
    this->setOriginToCenterForText();

    button.setPosition(x, y);
    buttonName.setPosition(x, y);
}

void Button::setSize(float width, float height)
{
    button.setSize({width, height});
}

void Button::setScale(float w, float h) {
    this->button.setScale(w, h);
}

void Button::setTexture(sf::Texture& texture) {
    this->button.setTexture(&texture);
}

int Button::getLocalBoundsWidth()
{
    return this->button.getLocalBounds().width;
}

int Button::getLocalBoundsHeight()
{
    return this->button.getLocalBounds().height;
}

int Button::getPositionX()
{
    return this->button.getPosition().x;
}

int Button::getPositionY()
{
    return this->button.getPosition().y;
}

int Button::getSizeWidth()
{
    return this->button.getSize().x;
}

int Button::getSizeHeight()
{
    return this->button.getSize().y;
}

void Button::drawTo(sf::RenderWindow &window)
{
    window.draw(button);
    window.draw(buttonName);
}

bool Button::isMouseOver(sf::RenderWindow &window)
{

    float xMouse = sf::Mouse::getPosition(window).x;
    float yMouse = sf::Mouse::getPosition(window).y;

    float topLeftX = button.getPosition().x - button.getLocalBounds().width / 2;
    float topLeftY = button.getPosition().y - button.getLocalBounds().height / 2;

    float limitRangeX = topLeftX + button.getLocalBounds().width;
    float limitRangeY = topLeftY + button.getLocalBounds().height;

    // std::cout << "mouse: " << xMouse << " "  << yMouse << std::endl;
    // std::cout << "limit: " << limitRangeX << " " << limitRangeY << std::endl;

    if (topLeftX < xMouse && xMouse < limitRangeX && topLeftY < yMouse && yMouse < limitRangeY)
    {
        return true;
    }
    return false;
}

void Button::setOriginToCenter() {
    this->button.setOrigin(this->button.getLocalBounds().width/2, this->button.getLocalBounds().height/2);
}

void Button::setOriginToCenterForText() {
    buttonName.setOrigin(buttonName.getLocalBounds().width / 2, buttonName.getLocalBounds().height / 2);
}