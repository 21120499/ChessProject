#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

/* this class is design for game manager as a state,
if you want to reuse it you have to adjust some parameters*/
class GameManager;
class Button;
class Popup
{
public:
sf::RectangleShape frame;
sf::Texture background;
sf::Text title;
sf::Text content;
sf::Font font;
std::vector<Button> choices;

public:
Popup();
Popup(sf::Vector2f size, sf::Vector2f pos, int nOfButton);
// void initTextField();
void initChoices();
void setFrameSize(sf::Vector2f);
void setTextSize(int size);
void setTitle(std::string title);
void setContent(std::string content);
void setFont(sf::Font &font);
void setFont(std::string filePath);
void setTextColor(sf::Color color);
void setBackground(sf::Texture &bgTexture);
void setBackground(std::string filePath);
void setBackgroundColor(sf::Color color);
void setChoiceString(std::string name, int index);
void setOriginCenterText();
void setChoiceButtonSize(int width, int height);
void setNumberOfChoice(int num);
void drawTo(sf::RenderWindow &window);
void setPosition(float x, float y);
sf::Vector2f getSizeFrame();
};
