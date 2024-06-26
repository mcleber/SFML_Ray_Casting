/**
 * @file    editor.hpp
 *
 * @brief   Creates the map editor with Panning and Zooming.
*/

#pragma once

#include <SFML/Graphics.hpp>

#include "../include/constants.hpp"
#include "map.hpp"

class Editor
{
    public:
        void init(sf::RenderWindow &window);
        void run(sf::RenderWindow &window, Map &map);

        void handleEvent(const sf::Event &event);

        std::string savedFileName;

    private:
        sf::RectangleShape cell;
        bool isFirstMouse{}; // Capture the mouse.
        sf::Vector2i lastMousePos;
        sf::View view;
        int textureNumber;
        int currentLayer;
};
