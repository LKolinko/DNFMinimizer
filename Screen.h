#pragma once
#include "Singleton.h"
#include <SFML/Graphics.hpp>
class Screen : public Singleton<Screen> {
public:
    sf::RenderWindow* window;
    void Init () {
        window = new sf::RenderWindow(sf::VideoMode(1000, 800), "BDSM maximizer");
    }
};