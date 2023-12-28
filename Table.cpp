#include "Table.h"
#include "iostream"
void Table::setData(std::vector<std::vector<int>> &a, std::vector<std::vector<std::string>> &data) {
    crossed_out_ = a;
    table_ = data;
}
void Table::DrawTo(sf::RenderWindow &wnd, sf::Font& font, float shift) {
    sf::Vector2u size = wnd.getSize();
    float shift_y = (float)size.y * shift / (float)(table_.size());
    float shift_x = (float)size.x * shift / (float)table_[0].size();
    for (int i = 1; i <= table_.size(); ++i) {
        sf::Vertex line[] = {sf::Vertex(sf::Vector2f(0, shift_y * i)),
                             sf::Vertex(sf::Vector2f(size.x * shift, shift_y * i))
        };
        line[0].color = sf::Color::Black;
        line[1].color = sf::Color::Black;
        wnd.draw(line, 2, sf::Lines);
    }
    for (int i = 1; i <= table_[0].size(); ++i) {
        sf::Vertex line[] = {sf::Vertex(sf::Vector2f(shift_x * i, 0)),
                             sf::Vertex(sf::Vector2f(shift_x * i, size.y * shift))
        };
        line[0].color = sf::Color::Black;
        line[1].color = sf::Color::Black;
        wnd.draw(line, 2, sf::Lines);
    }
    for (int i = 1; i <= table_.size(); ++i) {
        for (int j = 1; j <= table_[0].size(); ++j) {
            sf::Text text;
            text.setString(table_[i - 1][j - 1]);
            text.setFillColor(sf::Color::Black);
            text.setCharacterSize((int)(shift_y) * 0.8);
            text.setFont(font);
            text.setPosition({ shift_x * (j - 1) + shift_x / 2 - text.getLocalBounds().width / 2, shift_y * (i - 1) + shift_y / 2 - text.getLocalBounds().height });
            wnd.draw(text);
            sf::Vertex line[] = {sf::Vertex(sf::Vector2f(0, shift_y * (i - 1) + shift_y / 2 - 1)),
                                 sf::Vertex(sf::Vector2f(shift_x * j, shift_y * (i - 1) + shift_y / 2 - 1))
            };
            if (crossed_out_[i - 1][j - 1] == 1) {
                line[0].color = sf::Color::Blue;
                line[1].color = sf::Color::Blue;
                for (int k = -1; k <= 1; ++k) {
                    if (k != 0 && crossed_out_.size() >= (1 << 5) + 1) continue;
                    line[0].position = sf::Vector2f(0, shift_y * (i - 1) + shift_y / 2 + k);
                    line[1].position = sf::Vector2f(shift_x * j, shift_y * (i - 1) + shift_y / 2 + k);
                    wnd.draw(line, 2, sf::Lines);
                }
            } else if (crossed_out_[i - 1][j - 1]) {
                if (crossed_out_[i - 1][j - 1] == 2) {
                    line[0].color = sf::Color::Yellow;
                    line[1].color = sf::Color::Yellow;
                } else {
                    line[0].color = sf::Color::Red;
                    line[1].color = sf::Color::Red;
                }
                line[0].position = sf::Vector2f(shift_x * (j - 1), shift_y * i);

                line[1].position = sf::Vector2f(shift_x * j, shift_y * (i - 1));
                for (float k = -1; k <= 1; k += 0.5) {
                    if (k != 0 && crossed_out_.size() >= (1 << 5) + 1) continue;
                    line[0].position = sf::Vector2f(shift_x * (j - 1) + k * 0.7, shift_y * i + k * 0.7);
                    line[1].position = sf::Vector2f(shift_x * j + k * 0.7, shift_y * (i - 1) + k * 0.7);
                    wnd.draw(line, 2, sf::Lines);
                }
                for (float k = -1; k <= 1; k += 0.5) {
                    if (k != 0 && crossed_out_.size() >= (1 << 5) + 1) continue;
                    line[0].position = sf::Vector2f(shift_x * (j - 1) - k, shift_y * (i - 1) + k);
                    line[1].position = sf::Vector2f(shift_x * j - k, shift_y * i + k);
                    wnd.draw(line, 2, sf::Lines);
                }
            }
        }
    }
}