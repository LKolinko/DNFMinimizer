#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Singleton.h"
#include "Screen.h"
class TextLabel : public Singleton<TextLabel> {
public:
    sf::RenderWindow* window = Screen::GetInstance()->window;
    TextLabel() {
        strings.resize(1e5);
        strs_numbers_.resize(1e5);
    }
    ~TextLabel() = default;
    void Create(sf::Font& font) {
        sf::Vector2u windowSize = window->getSize();
        size_ = sf::Vector2f((float)(windowSize.x) * 0.8, (float)(windowSize.y) * 0.18);
        textlable_.setSize(size_);
        title_.setFont(font);
        title_.setString("Result:");
        title_.setFillColor(sf::Color::Black);
        title_.setCharacterSize(textlable_.getLocalBounds().height / 4);
        textlable_.setPosition(0, (float)windowSize.y * 0.81);
        title_.setPosition(textlable_.getPosition().x, textlable_.getPosition().y);
        sf::Vector2f p = textlable_.getPosition();
        for (int i = start_; i < start_ + size_.y / (title_.getLocalBounds().height * 1.5) - 2; ++i) {
            p.y += title_.getLocalBounds().height * 1.65;
            strs_numbers_[i].setFont(font);
            strs_numbers_[i].setFillColor(sf::Color::Black);
            strs_numbers_[i].setPosition(p);
            strs_numbers_[i].setCharacterSize(title_.getCharacterSize() * 0.9);
            strs_numbers_[i].setString(std::to_string(i + 1) + ".");
        }
    }
    void SetColor() {
        textlable_.setFillColor(sf::Color(205, 198, 165));
    }
    sf::Vector2f getSize() {
        return size_;
    }
    float getSizeText(int n) {
        return textlable_.getSize().x - strs_numbers_[n].getLocalBounds().width - 3;
    }
    void setStrings(std::vector<std::string>& a) {
        strings.assign(1e5, { });
        stringsSize_ = a.size();
        for (int i = 0; i < a.size(); ++i) {
            sf::Text text;
            text.setFillColor(sf::Color::Black);
            text.setString(a[i]);
            strings[i] = text;
        }
    }
    void drawTo(sf::Font& font) {
        window->draw(textlable_);
        window->draw(title_);
        for (int i = start_; i < start_ + size_.y / (title_.getLocalBounds().height * 1.5) - 2; ++i) {
            if (i < stringsSize_) {
                std::string str = strings[i].getString();
                sf::Text t;
                t.setString("B");
                t.setFont(font);
                t.setCharacterSize(strs_numbers_[i].getCharacterSize());
                sf::Vector2f pos = {strs_numbers_[i].getPosition().x + strs_numbers_[i].getLocalBounds().width + 10, strs_numbers_[i].getPosition().y};
                float shift_x = t.getLocalBounds().height;
                for (int j = 0; j < str.size(); ++j) {
                    if (str[j] >= 'a' && str[j] <= 'z' && str[j] != 'v' && str[j] != ' ') {
                        for (int k = -1; k <= 1; ++k) {
                            sf::Vertex line[] = {sf::Vertex(sf::Vector2f(pos.x + shift_x * j, pos.y + 5 + k)),
                                                 sf::Vertex(sf::Vector2f(pos.x + shift_x * (j + 1), pos.y + 5 + k))
                            };
                            line[0].color = sf::Color::Black;
                            line[1].color = sf::Color::Black;
                            window->draw(line, 2, sf::Lines);
                        }
                    }
                }
            }
            if (i < stringsSize_) {
                std::string str = strings[i].getString();
                for (int j = 0; j < str.size(); ++j) {
                    if (str[j] >= 'a' && str[j] <= 'z' && str[j] != 'v' && str[j] != ' ') {
                        str[j] = char(str[j] - 32);
                    }
                }
                sf::Text txt;
                txt.setString(str);
                txt.setPosition(strs_numbers_[i].getPosition().x + strs_numbers_[i].getLocalBounds().width + 10, strs_numbers_[i].getPosition().y);
                txt.setFont(font);
                txt.setFillColor(sf::Color::Black);
                txt.setCharacterSize(strs_numbers_[i].getCharacterSize());
                window->draw(txt);
            }
            window->draw(strs_numbers_[i]);
        }
    }
    void setActive(bool Active) {
        if (Active) {
            textlable_.setFillColor(sf::Color(233, 198, 165));
        } else {
            textlable_.setFillColor(sf::Color(205, 198, 165));
        }
        is_active = Active;
    }
    bool isMousOver(sf::RenderWindow& wnd) {
        int mouseX = sf::Mouse::getPosition(wnd).x;
        int mouseY = sf::Mouse::getPosition(wnd).y;
        int btnPosX = textlable_.getPosition().x;
        int btnPosY = textlable_.getPosition().y;
        int btnxPosWidth = textlable_.getPosition().x + textlable_.getLocalBounds().width;
        int btnyPosHeight = textlable_.getPosition().y + textlable_.getLocalBounds().height;
        if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
            return true;
        }
        return false;
    }
    void Scroll(sf::Event& event, sf::Font& font) {
        if (is_active) {
            if (event.type == sf::Event::TextEntered && event.key.code == 97) {
                if (start_ != 0) {
                    --start_;
                }
            }
            if (event.type == sf::Event::TextEntered && event.key.code == 122) {
                ++start_;
            }
            Create(font);
        }
    }
private:
    bool is_passed = false;
    bool is_active = false;
    int start_ = 0;
    int stringsSize_ = 0;
    std::vector<sf::Text> strs_numbers_;
    std::vector<sf::Text> strings;
    sf::Text title_;
    sf::Vector2f size_;
    sf::RectangleShape textlable_;
};