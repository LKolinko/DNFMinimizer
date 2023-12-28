#pragma once
#include "Screen.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
class Button {
public:
	Button() = default;
	void SetText(std::string btnText, sf::Color textColor, sf::Font& font) {
		text.setFont(font);
		text.setString(btnText);
		text.setCharacterSize(button.getLocalBounds().height / 2.5);
		text.setFillColor(textColor);
	}
	void SetBackColor(sf::Color color) {
		button.setFillColor(color);
	}
	void SetSize(sf::Vector2f size) {
		button.setSize(size);
		btnWidth = size.x;
		btnHeight = size.y;
	}
	void SetPosition(sf::Vector2f point) {
		button.setPosition(point);
		float xPos = (point.x + btnWidth / 2) - (text.getLocalBounds().width / 2);
		float yPos = (point.y + btnHeight / 2.7) - (text.getLocalBounds().height / 2);
		text.setPosition(xPos, yPos);
	}
	void Draw_To(sf::RenderWindow& window) {
		window.draw(button);
		window.draw(text);
	}
	bool isMouseOver(sf::RenderWindow& window) {
		int mouseX = sf::Mouse::getPosition(window).x;
		int mouseY = sf::Mouse::getPosition(window).y;
		int btnPosX = button.getPosition().x;
		int btnPosY = button.getPosition().y;
		int btnxPosWidth = button.getPosition().x + btnWidth;
		int btnyPosHeight = button.getPosition().y + btnHeight;
		if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
            this->SetBackColor(sf::Color(111, 146, 131));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                this->SetBackColor(sf::Color(105, 109, 125));
                if (!is_cliced) {
                    is_cliced = true;
                    return true;
                }
            } else {
                is_cliced = false;
            }
		} else {
            this->SetBackColor(sf::Color(141, 159, 135));
        }
        return false;
	}

private:
    bool is_cliced = false;
	sf::RectangleShape button;
	sf::Text text;
	int btnWidth;
	int btnHeight;
};

