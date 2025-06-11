//
// Created by chris on 04/06/2025.
//

#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include <memory>
#include "utils/Level.h"

class LevelLoader {
public:
    static std::shared_ptr<Level> loadLevel(int levelNumber) {
        auto level = std::make_shared<Level>(levelNumber);

        switch (levelNumber) {
            case 1:
                configureLevelOne(level);
                break;
            case 2:
                configureLevelTwo(level);
                break;
            // here to add more levels
            default:
                return nullptr;
        }

        return level->isValid() ? level : nullptr;
    }

private:
    static void configureLevelOne(const std::shared_ptr<Level>& level) {
        // Create nodes
        auto spawn = std::make_shared<PathNode>(0, "spawn", GridPosition(5, 1));   // Begin down left
        auto path1 = std::make_shared<PathNode>(1, "path", GridPosition(5, 3));    // right
        auto path2 = std::make_shared<PathNode>(2, "path", GridPosition(2, 3));    // up
        auto path3 = std::make_shared<PathNode>(3, "path", GridPosition(2, 6));    // right
        auto path4 = std::make_shared<PathNode>(4, "path", GridPosition(5, 6));    // Down
        auto base = std::make_shared<PathNode>(5, "base", GridPosition(5, 9));     // Base at the right

        // Add nodes to level
        level->addNode(spawn);
        level->addNode(path1);
        level->addNode(path2);
        level->addNode(path3);
        level->addNode(path4);
        level->addNode(base);

        // Connect nodes to create the path
        Level::connectNodes(spawn, path1);
        Level::connectNodes(path1, path2);
        Level::connectNodes(path2, path3);
        Level::connectNodes(path3, path4);
        Level::connectNodes(path4, base);

        // Add tower spots avec GridPosition
        level->addTowerSpot(GridPosition(3, 3).toPixelPosition());
        level->addTowerSpot(GridPosition(1, 5).toPixelPosition());
        level->addTowerSpot(GridPosition(3, 5).toPixelPosition());
        level->addTowerSpot(GridPosition(3, 7).toPixelPosition());
    }

    static void configureLevelTwo(const std::shared_ptr<Level>& level) {
        // Config for level 2
        auto spawn = std::make_shared<PathNode>(0, "spawn", GridPosition(1, 1));
        auto path1 = std::make_shared<PathNode>(1, "path", GridPosition(1, 3));
        auto path2 = std::make_shared<PathNode>(2, "path", GridPosition(5, 3));
        auto path3 = std::make_shared<PathNode>(3, "path", GridPosition(5, 7));
        auto base = std::make_shared<PathNode>(4, "base", GridPosition(5, 9));

        // Add nodes to level
        level->addNode(spawn);
        level->addNode(path1);
        level->addNode(path2);
        level->addNode(path3);
        level->addNode(base);

        // Connect nodes to create the path
        Level::connectNodes(spawn, path1);
        Level::connectNodes(path1, path2);
        Level::connectNodes(path2, path3);
        Level::connectNodes(path3, base);

        // Add tower spots
        level->addTowerSpot(GridPosition(2, 2).toPixelPosition());
        level->addTowerSpot(GridPosition(3, 5).toPixelPosition());
        level->addTowerSpot(GridPosition(3, 7).toPixelPosition());
    }
};

#endif //LEVELLOADER_H
