//
// Created by chris on 04/06/2025.
//
#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <memory>
#include "../utils/Position.h"
#include "../utils/PathNode.h"
#include "../utils/GridPosition.h"

class Level {
private:
    int levelNumber;
    std::vector<std::shared_ptr<PathNode>> nodes;
    std::shared_ptr<PathNode> spawnPoint;
    std::shared_ptr<PathNode> basePoint;
    std::vector<Position> towerSpots;

public:
    explicit Level(int number) : levelNumber(number) {}

    // Getters
    int getLevelNumber() const { return levelNumber; }
    const std::vector<std::shared_ptr<PathNode>>& getNodes() const { return nodes; }
    std::shared_ptr<PathNode> getSpawnPoint() const { return spawnPoint; }
    std::shared_ptr<PathNode> getBasePoint() const { return basePoint; }
    const std::vector<Position>& getTowerSpots() const { return towerSpots; }

    // Construct level
    void addNode(const std::shared_ptr<PathNode>& node) {
        if (node->getType() == "spawn") spawnPoint = node;
        else if (node->getType() == "base") basePoint = node;
        nodes.push_back(node);
    }

    // Add tower spot
    void addTowerSpot(const Position& pos) {
        towerSpots.push_back(pos);
    }

    //Verify if a position is a valid position for a tower
    bool isValidTowerPosition(const Position& position) const {
        // Convert position in grid coordinates
        GridPosition posGrid = GridPosition::fromPixelPosition(position);

        // Verify each tower spot
        for (const auto& spot : towerSpots) {
            GridPosition spotGrid = GridPosition::fromPixelPosition(spot);
            if (spotGrid.col == posGrid.col && spotGrid.row == posGrid.row) {
                return true;
            }
        }
        return false;
    }

    // Verify if a grid position is a valid place for a tower
    bool isValidTowerGridPosition(const GridPosition& gridPos) const {
        for (const auto& spot : towerSpots) {
            GridPosition spotGrid = GridPosition::fromPixelPosition(spot);
            if (spotGrid.col == gridPos.col && spotGrid.row == gridPos.row) {
                return true;
            }
        }
        return false;
    }

    // Connect nodes
    static void connectNodes(const std::shared_ptr<PathNode>& from, std::shared_ptr<PathNode> to) {
        from->addConnection(std::move(to));
    }

    // Validate level
    bool isValid() const {
        return spawnPoint != nullptr && basePoint != nullptr && !nodes.empty();
    }
};

#endif //LEVEL_H