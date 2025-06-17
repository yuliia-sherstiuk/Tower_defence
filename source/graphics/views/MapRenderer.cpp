//
// Created by chris on 16/06/2025.
//

#include "../../../includes/graphics/views/MapRenderer.h"
#include "../../../includes/graphics/views/EnemyRenderer.h"
#include "../../../includes/logic/models/Enemy.h"
#include "../../../includes/logic/models/Wave.h"

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
    , levelDebugPrinted(false)
    , enemyRenderer(std::make_unique<EnemyRenderer>())
{
    if (!baseTexture.loadFromFile("assets/sprites/base.png")) {
        std::cerr << "Failed to load base texture!" << std::endl;
    }
    baseSprite.setTexture(baseTexture);
    baseSprite.setScale(CELL_SIZE / baseTexture.getSize().x,
                       CELL_SIZE / baseTexture.getSize().y);
}

void MapRenderer::setLevel(const std::shared_ptr<Level>& level) {
    currentLevel = level;
    levelDebugPrinted = false; // Reset flag for new level
    std::cout << "[DEBUG] MapRenderer: Setting new level" << std::endl;
}

// Add method to set current wave
void MapRenderer::setCurrentWave(const std::shared_ptr<Wave>& wave) {
    currentWave = wave;
    std::cout << "[DEBUG] MapRenderer: Setting current wave" << std::endl;
}

void MapRenderer::render() {
    if (!currentLevel) return;

    renderGrid();
    renderLevelElements();
    renderTowerSpots();
    renderEnemies();

    // Print debug info only once per level
    if (!levelDebugPrinted) {
        printLevelDebugInfo();
        levelDebugPrinted = true;
    }
}

// Method to render enemies
void MapRenderer::renderEnemies() {
    if (!currentWave || !enemyRenderer) return;

    const auto& enemies = currentWave->getEnemies();
    for (const auto& enemy : enemies) {
        if (enemy && !enemy->isDead()) {
            enemyRenderer->renderEnemy(enemy, window);
        }
    }
}

void MapRenderer::printLevelDebugInfo() {
    std::cout << "[DEBUG] MapRenderer: Level loaded with:" << std::endl;

    // Print detailed info with coordinates
    for (const auto& node : currentLevel->getNodes()) {
        const GridPosition& nodePos = node->getGridPosition();
        const std::string& nodeType = node->getType();

        if (nodeType == "spawn") {
            std::cout << "[DEBUG] - Spawn at (" << nodePos.col << "," << nodePos.row << ")" << std::endl;
        }
        else if (nodeType == "path") {
            std::cout << "[DEBUG] - Path at (" << nodePos.col << "," << nodePos.row << ")" << std::endl;
        }
        else if (nodeType == "base") {
            std::cout << "[DEBUG] - Base at (" << nodePos.col << "," << nodePos.row << ")" << std::endl;
        }
    }

    // Print tower spots with coordinates
    for (const auto& spot : currentLevel->getTowerSpots()) {
        GridPosition gridPos = GridPosition::fromPixelPosition(spot);
        std::cout << "[DEBUG] - Tower spot at (" << gridPos.col << "," << gridPos.row << ")" << std::endl;
    }
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
    // First, render the complete enemy path
    renderEnemyPath();

    // Then render special nodes (spawn, base) on top
    for (const auto& node : currentLevel->getNodes()) {
        const GridPosition& nodePos = node->getGridPosition();
        float x = GAME_FIELD_X + nodePos.col * CELL_SIZE;
        float y = GAME_FIELD_Y + nodePos.row * CELL_SIZE;

        const std::string& nodeType = node->getType();
        if (nodeType == "spawn") {
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
            cell.setPosition(x, y);
            cell.setFillColor(spawnColor);
            window.draw(cell);
        }
        else if (nodeType == "base") {
            baseSprite.setPosition(x, y);
            window.draw(baseSprite);
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

    }
}

void MapRenderer::renderEnemyPath() {
    // Find the spawn node
    std::shared_ptr<PathNode> currentNode = nullptr;
    for (const auto& node : currentLevel->getNodes()) {
        if (node->getType() == "spawn") {
            currentNode = node;
            break;
        }
    }

    if (!currentNode) return;

    std::set<std::pair<int, int>> visitedNodes;

    while (currentNode) {
        const GridPosition& currentPos = currentNode->getGridPosition();
        std::pair<int, int> nodeKey = {currentPos.col, currentPos.row};

        if (visitedNodes.find(nodeKey) != visitedNodes.end()) {
            break;
        }
        visitedNodes.insert(nodeKey);

        // Get next node
        const auto& connections = currentNode->getConnections();
        if (connections.empty()) break;

        std::shared_ptr<PathNode> nextNode = connections[0];
        if (!nextNode) break;

        const GridPosition& nextPos = nextNode->getGridPosition();

        // Draw path between current and next node
        int startCol = currentPos.col;
        int startRow = currentPos.row;
        int endCol = nextPos.col;
        int endRow = nextPos.row;

        // Determine direction and draw all cells between nodes
        if (startCol == endCol) {
            // Vertical path
            int step = (endRow > startRow) ? 1 : -1;
            for (int row = startRow; row != endRow + step; row += step) {
                sf::RectangleShape pathCell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
                pathCell.setPosition(GAME_FIELD_X + startCol * CELL_SIZE,
                                   GAME_FIELD_Y + row * CELL_SIZE);
                pathCell.setFillColor(pathColor);
                window.draw(pathCell);
            }
        } else if (startRow == endRow) {
            // Horizontal path
            int step = (endCol > startCol) ? 1 : -1;
            for (int col = startCol; col != endCol + step; col += step) {
                sf::RectangleShape pathCell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
                pathCell.setPosition(GAME_FIELD_X + col * CELL_SIZE,
                                   GAME_FIELD_Y + startRow * CELL_SIZE);
                pathCell.setFillColor(pathColor);
                window.draw(pathCell);
            }
        }

        currentNode = nextNode;
        if (currentNode->getType() == "base") break;
    }
}