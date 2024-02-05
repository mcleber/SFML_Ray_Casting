/**
 * @file    renderer.cpp
 *
 * @brief   Creates the "3D" version of the map.
*/

#include <cmath>
#include <cstddef>
#include <algorithm>

#include "../include/renderer.hpp"

struct Ray
{
    sf::Vector2f hitPosition;
    sf::Vector2u mapPosition;
    float distance;
    bool hit;
    bool isHitVertical;
};

//static Ray castRay(sf::Vector2f start, float angleInDegrees, const Map &map);

void Renderer::init()
{
    if (!wallTexture.loadFromFile("./image/wall_texture.png"))
    {
        std::cerr << "Failed to load wall_texture.png" << std::endl;

        return;
    }

    if (wallTexture.getSize().x != wallTexture.getSize().y)
    {
        std::cerr << "ERROR: Texture is not square" << std::endl;

        return;
    }

    wallSprite = sf::Sprite(wallTexture);
}

void Renderer::draw3DView(sf::RenderTarget &target, const Player &player, const Map &map)
{
    /// Creates the ground and the sky
    sf::RectangleShape rectangle(sf::Vector2f(SCREEN_W, SCREEN_H / 2.0f));
    rectangle.setFillColor(sf::Color(100, 170, 250)); // Céu
    target.draw(rectangle);

    rectangle.setPosition(0.0f, SCREEN_H / 2.0f); // Chão
    rectangle.setFillColor(sf::Color(70, 70, 70));
    target.draw(rectangle);

    const sf::Color fogColor = sf::Color(100, 170, 250);
    const float maxRenderDistance = MAX_RAYCASTING_DEPTH * map.getCellSize();
    const float maxFogDistance = maxRenderDistance / 4.0f;

    float radians = player.angle * PI / 180.0f;
    sf::Vector2f directions{std::cos(radians),std::sin(radians)};
    sf::Vector2f plane{-directions.y, directions.x}; //plane camera

    sf::VertexArray walls{sf::Lines};

    for (size_t i = 0; i < SCREEN_W; i++)
    {
        float cameraX = i * 2.0f / SCREEN_W - 1.0f; // -1.0f -> 0.0f -> 1.0f

        sf::Vector2f rayPos = player.position / map.getCellSize();
        sf::Vector2f rayDir = directions + plane * cameraX;

        sf::Vector2f deltaDist{std::abs(1.0f / rayDir.x), std::abs(1.0f / rayDir.y)};

        sf::Vector2i mapPos{rayPos};
        sf::Vector2i step;
        sf::Vector2f sideDist;

        if (rayDir.x < 0.0f)
        {
            step.x = -1;
            sideDist.x = (-mapPos.x + rayPos.x) * deltaDist.x;
        } else
        {
            step.x = 1;
            sideDist.x = (mapPos.x - rayPos.x + 1.0f) * deltaDist.x;
        }

        if (rayDir.y < 0.0f)
        {
            step.y = -1;
            sideDist.y = (-mapPos.y + rayPos.y) * deltaDist.y;
        }
        else
        {
            step.y = 1;
            sideDist.y = (mapPos.y - rayPos.y + 1.0f) * deltaDist.y;
        }

        bool didHit{}, isHitVertical{};
        size_t depth = 0;
        while (!didHit && depth < MAX_RAYCASTING_DEPTH)
        {
            if (sideDist.x < sideDist.y)
            {
                sideDist.x += deltaDist.x;
                mapPos.x += step.x;
                isHitVertical = false;
            }
            else
            {
                sideDist.y += deltaDist.y;
                mapPos.y += step.y;
                isHitVertical = true;
            }

            int x = mapPos.x, y = mapPos.y;
            const auto &grid = map.getGrid();

            if (x >= 0 && y < grid.size() && x >= 0 && x < grid[y].size() &&
                grid[y][x] != sf::Color::Black)
            {
                didHit = true;
            }

            depth++;
        }

        float perpWallDist = isHitVertical ? sideDist.y - deltaDist.y : sideDist.x - deltaDist.x;
        float wallHeight = SCREEN_H / perpWallDist;

        float wallStart = (-wallHeight + SCREEN_H) / 2.0f;
        float wallEnd = (wallHeight + SCREEN_H) / 2.0f;

        walls.append(sf::Vertex(sf::Vector2f((float)i, wallStart)));
        walls.append(sf::Vertex(sf::Vector2f((float)i, wallEnd)));
    }

    target.draw(walls);
}
