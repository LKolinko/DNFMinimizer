#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class TextBox {
public:
    void SetSize(sf::Vector2f size);
    void SetPosition(sf::Vector2f pos);
    void SetBackColor(sf::Color color);
    void SetFont(sf::Font& font);
    void enter(sf::Event& event);
    bool isMousOver(sf::RenderWindow& wnd);
    void Draw_To(sf::RenderWindow& wnd);
    void SetTitle(sf::Font& font, std::string& str);
    void setActive(bool Active);
    std::string get_text();
    void set_text(std::string str);
    void text_size();
    void SetStart();
private:
    int start = 0;
    int TextBoxWidth;
    int TextBoxHeight;
    bool is_active = false;
    sf::RectangleShape back;
    std::string str_;
    sf::Text text_;
    sf::Text title;
};
