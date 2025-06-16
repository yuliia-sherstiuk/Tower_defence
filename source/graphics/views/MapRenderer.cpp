//
// Created by chris on 16/06/2025.


#include "../../../includes/graphics/views/MapRenderer.h"

const float MapRenderer::CELL_SIZE = 60.0f;
const float MapRenderer::GAME_FIELD_X = 20.0f;
const float MapRenderer::GAME_FIELD_Y = 260.0f;

MapRenderer::MapRenderer(sf::RenderWindow& window)
    : window(window)
    , spawnColor(128, 128, 128)
    , pathColor(192, 192, 192)
    , towerSpotColor(100, 200, 100)
    , defaultColor(50, 50, 50)
    , gridColor(70, 70, 70)
{
    if (!baseTexture.loadFromFile("assets/base.png")) {
        std::cerr << "Failed to load base texture!" << std::endl;
    }
    baseSprite.setTexture(baseTexture);
    baseSprite.setScale(CELL_SIZE / baseTexture.getSize().x,
                       CELL_SIZE / baseTexture.getSize().y);
}

void MapRenderer::setLevel(const std::shared_ptr<Level>& level) {
    currentLevel = level;
    std::cout << "[DEBUG] MapRenderer: Setting new level" << std::endl;
}

void MapRenderer::render() {
    if (!currentLevel) return;

    renderGrid();
    renderLevelElements();
    renderTowerSpots();
}

void MapRenderer::renderGrid() {
    for (int row = 0; row < 18; ++row) {
        for (int col = 0; col < 28; ++col) {
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
            cell.setPosition(GAME_FIELD_X + col * CELL_SIZE,
                           GAME_FIELD_Y + row * CELL_SIZE);
            cell.setFillColor(defaultColor);
            cell.setOutlineColor(gridColor);
            cell.setOutlineThickness(1);
            window.draw(cell);
        }
    }
}

void MapRenderer::renderLevelElements() {
    for (const auto& node : currentLevel->getNodes()) {
        sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
        const GridPosition& nodePos = node->getGridPosition();
        float x = GAME_FIELD_X + nodePos.col * CELL_SIZE;
        float y = GAME_FIELD_Y + nodePos.row * CELL_SIZE;
        cell.setPosition(x, y);

        const std::string& nodeType = node->getType();
        if (nodeType == "spawn") {
            cell.setFillColor(spawnColor);
            window.draw(cell);
            std::cout << "[DEBUG] MapRenderer: Drawing spawn at ("
                     << nodePos.col << "," << nodePos.row << ")" << std::endl;
        }
        else if (nodeType == "path") {
            cell.setFillColor(pathColor);
            window.draw(cell);
            std::cout << "[DEBUG] MapRenderer: Drawing path at ("
                     << nodePos.col << "," << nodePos.row << ")" << std::endl;
        }
        else if (nodeType == "base") {
            baseSprite.setPosition(x, y);
            window.draw(baseSprite);
            std::cout << "[DEBUG] MapRenderer: Drawing base at ("
                     << nodePos.col << "," << nodePos.row << ")" << std::endl;
        }

        const auto& connections = node->getConnections();
        if (!connections.empty()) {
            for (const auto& connectedNode : connections) {
                sf::RectangleShape line(sf::Vector2f(2, 2));
                line.setFillColor(sf::Color::Yellow);

                float startX = x + CELL_SIZE / 2;
                float startY = y + CELL_SIZE / 2;

                const GridPosition& connPos = connectedNode->getGridPosition();
                float endX = GAME_FIELD_X + connPos.col * CELL_SIZE + CELL_SIZE / 2;
                float endY = GAME_FIELD_Y + connPos.row * CELL_SIZE + CELL_SIZE / 2;

                float length = std::sqrt(std::pow(endX - startX, 2) + std::pow(endY - startY, 2));
                float angle = std::atan2(endY - startY, endX - startX) * 180 / 3.14159f;

                line.setSize(sf::Vector2f(length, 2));
                line.setPosition(startX, startY);
                line.setRotation(angle);

                window.draw(line);
            }
        }
    }
}

void MapRenderer::renderTowerSpots() {
    for (const auto& spot : currentLevel->getTowerSpots()) {
        sf::RectangleShape towerSpot(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
        GridPosition gridPos = GridPosition::fromPixelPosition(spot);
        towerSpot.setPosition(GAME_FIELD_X + gridPos.col * CELL_SIZE,
                            GAME_FIELD_Y + gridPos.row * CELL_SIZE);
        towerSpot.setFillColor(towerSpotColor);
        window.draw(towerSpot);
        std::cout << "[DEBUG] MapRenderer: Drawing tower spot at ("
                 << gridPos.col << "," << gridPos.row << ")" << std::endl;
    }
}