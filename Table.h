#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Table {
public:
    Table() = default;
    ~Table() = default;
    void setData(std::vector<std::vector<int>>& a, std::vector<std::vector<std::string>>& data);
    void DrawTo(sf::RenderWindow& wnd, sf::Font& font, float shift);
private:
    std::vector<std::vector<int>> crossed_out_;
    std::vector<std::vector<std::string>> table_;
};