#include "Popup.h"
#include "Button.hpp"

Popup::Popup() : Popup::Popup({400, 200}, {0, 0}, 2)
{
}

Popup::Popup(sf::Vector2f size, sf::Vector2f pos, int nOfButton)
{
    this->frame.setSize(size);
    this->setPosition(pos.x, pos.y);
    this->frame.setFillColor(sf::Color(209, 77, 114, 200));

    this->choices.resize(nOfButton);
    this->initChoices();
}

void Popup::setBackground(sf::Texture &bgTexture)
{
    this->frame.setTexture(&bgTexture);
}

void Popup::setBackground(std::string filePath)
{
    if (!this->background.loadFromFile(filePath))
    {
        std::cout << "Cannot load bg image for popup" << std::endl;
    }
    else
    {
        this->frame.setTexture(&this->background);
    }
}

void Popup::setFont(sf::Font &font)
{
    this->font = font;
    this->title.setFont(this->font);
    this->content.setFont(this->font);
    for (int i = 0; i < choices.size(); ++i)
    {
        this->choices[i].setFont(this->font);
    }
}

void Popup::setBackgroundColor(sf::Color color)
{
    this->frame.setFillColor(color);
}

void Popup::setFont(std::string filePath)
{
    if (!this->font.loadFromFile(filePath))
    {
        std::cout << "Load font in class Popup fail" << std::endl;
    }
    else
    {
        this->title.setFont(this->font);
        this->content.setFont(this->font);
        for (int i = 0; i < choices.size(); ++i)
        {
            this->choices[i].setFont(this->font);
        }
    }
}

void Popup::setTextColor(sf::Color color)
{
    this->title.setFillColor(color);
    this->content.setFillColor(color);
}

void Popup::setOriginCenterText()
{
    this->title.setOrigin(this->title.getLocalBounds().width / 2, this->title.getLocalBounds().height / 2);
    this->content.setOrigin(this->content.getLocalBounds().width / 2, this->content.getLocalBounds().height / 2);
}

void Popup::setChoiceButtonSize(int width, int height)
{
    for (int i = 0; i < this->choices.size(); ++i)
    {
        this->choices[i].setSize(width, height);
    }
}

/* void Popup::initTextField() {
    this->font.loadFromFile("Asset/Pacifico.ttf");
    this->title.setFont(this->font);
    this->title.setCharacterSize(27);
    this->content.setFont(this->font);
    this->content.setCharacterSize(20);

} */

void Popup::initChoices()
{
    int nOfChoice = this->choices.size();
    int partPixel = this->frame.getSize().x / (nOfChoice * 2);
    int startPointX = this->frame.getPosition().x;
    int yPos = this->frame.getPosition().y + this->frame.getSize().y - 60;
    for (int i = 0; i < nOfChoice; ++i)
    {
        this->choices[i].setBackgroundColor(sf::Color(238, 130, 238, 100));
        this->choices[i].setSize(60, 30);
        this->choices[i].setTitle("Button");
        this->choices[i].setFont(this->font);
        this->choices[i].setTextSize(16);
        this->choices[i].setTextColor(sf::Color::White);
        this->choices[i].setPosition(startPointX + partPixel + 2 * i * partPixel, yPos);
    }
}

void Popup::setFrameSize(sf::Vector2f size)
{
    this->frame.setSize(size);

    // we have to call this method to arrange all contents inside
    // frame when update
    this->setPosition(size.x, size.y);
}

void Popup::setTextSize(int size)
{
    this->title.setCharacterSize(size + 4);
    this->content.setCharacterSize(size);
}

void Popup::setTitle(std::string title)
{
    this->title.setString(title);
    this->setOriginCenterText();
}

void Popup::setContent(std::string content)
{
    this->content.setString(content);
    this->setOriginCenterText();
}

void Popup::setChoiceString(std::string name, int index)
{
    this->choices[index].setTitle(name);
    this->choices[index].setOriginToCenterForText();
}

void Popup::drawTo(sf::RenderWindow &window)
{
    window.draw(this->frame);
    window.draw(this->title);
    window.draw(this->content);

    for (int i = 0; i < this->choices.size(); ++i)
    {
        this->choices[i].drawTo(window);
    }
}

void Popup::setPosition(float x, float y)
{
    this->frame.setPosition({x, y});

    this->setOriginCenterText();
    this->title.setPosition(x + this->frame.getSize().x / 2,
                            y + 60);
    this->content.setPosition(x + this->frame.getSize().x / 2,
                              y + this->frame.getSize().y / 2);

    int nOfChoice = this->choices.size();
    int partPixel = this->frame.getSize().x / (nOfChoice * 2);
    int yPos = y + this->frame.getSize().y - 60;
    for (int i = 0; i < nOfChoice; ++i)
    {
        this->choices[i].setPosition(x + partPixel + 2 * i * partPixel, yPos);
    }
}

void Popup::setNumberOfChoice(int num)
{
    this->choices.erase(this->choices.begin(), this->choices.end());
    this->choices.resize(num);
    this->initChoices();
}

sf::Vector2f Popup::getSizeFrame()
{
    return this->frame.getSize();
}
