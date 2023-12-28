#include "TextBox.h"
void TextBox::SetSize(sf::Vector2f size) {
    back.setSize(size);
    TextBoxWidth = size.x;
    TextBoxHeight = size.y;
}
void TextBox::SetBackColor(sf::Color color) {
    back.setFillColor(color);
}
void TextBox::SetPosition(sf::Vector2f pos) {
    back.setPosition(pos);
    float xPos = (pos.x + TextBoxWidth / 2);
    float yPos = (pos.y + TextBoxHeight / 2.7);
    text_.setPosition(xPos, yPos);
}
void TextBox::Draw_To(sf::RenderWindow& wnd) {
    wnd.draw(back);
    wnd.draw(text_);
    wnd.draw(title);
}
void TextBox::SetTitle(sf::Font &font, std::string& str) {
    title.setString(str);
    title.setFillColor(sf::Color::Black);
    title.setCharacterSize((back.getLocalBounds().height) / 4);
    title.setFont(font);
    title.setPosition(back.getPosition());
}
void TextBox::setActive(bool Active) {
    if (Active) {
        back.setFillColor(sf::Color(233, 198, 165));
    } else {
        back.setFillColor(sf::Color(205, 198, 165));
    }
    is_active = Active;
}
void TextBox::SetFont(sf::Font &font) {
    text_.setFont(font);
    text_.setFont(font);
}
void TextBox::enter(sf::Event& event) {
    if (is_active) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (start != 0) {
                --start;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (start != str_.size() - 1) {
                ++start;
            }
        }
        if (event.type == sf::Event::TextEntered) {
            if (event.key.code == 8 || event.key.code == 127) {
                if (!str_.empty()) {
                    str_.pop_back();
                }
            } else {
                char c[] = {event.key.code};
                str_.push_back(c[0]);
            }
        }
    }
    text_size();
}
std::string TextBox::get_text() {
    return str_;
}
void TextBox::set_text(std::string str) {
    str_ = str;
    text_size();
}
void TextBox::text_size() {
    std::string text_string = "";
    for (int i = start; i < str_.size(); ++i) {
        text_string += str_[i];
        text_.setCharacterSize(back.getLocalBounds().height / 4);
        text_.setString(text_string);
        if (text_.getLocalBounds().width > back.getLocalBounds().width - text_.getCharacterSize()) {
            text_string.pop_back();
        }
    }
    text_.setFillColor(sf::Color::Black);
    text_.setCharacterSize(back.getLocalBounds().height / 4);
    text_.setString(text_string);
    text_.setPosition({ back.getPosition().x, back.getPosition().y + TextBoxHeight / 2 });
}
bool TextBox::isMousOver(sf::RenderWindow& wnd) {
    int mouseX = sf::Mouse::getPosition(wnd).x;
    int mouseY = sf::Mouse::getPosition(wnd).y;
    int btnPosX = back.getPosition().x;
    int btnPosY = back.getPosition().y;
    int btnxPosWidth = back.getPosition().x + TextBoxWidth;
    int btnyPosHeight = back.getPosition().y + TextBoxHeight;
    if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
        return true;
    }
    return false;
}
void TextBox::SetStart() {
    start = 0;
}
