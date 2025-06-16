//
// Created by chris on 04/06/2025.
//

#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include <memory>
#include "../utils/Level.h"
#include "../utils/GridPosition.h"

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
        // Create nodes with path covering the map (16 width, 26 height)
        auto spawn = std::make_shared<PathNode>(0, "spawn", GridPosition(2, 1));
        auto path1 = std::make_shared<PathNode>(1, "path", GridPosition(2, 6));
        auto path2 = std::make_shared<PathNode>(2, "path", GridPosition(8, 6));
        auto path3 = std::make_shared<PathNode>(3, "path", GridPosition(8, 12));
        auto path4 = std::make_shared<PathNode>(4, "path", GridPosition(4, 12));
        auto path5 = std::make_shared<PathNode>(5, "path", GridPosition(4, 16));
        auto path6 = std::make_shared<PathNode>(6, "path", GridPosition(12, 16));
        auto path7 = std::make_shared<PathNode>(7, "path", GridPosition(12, 20));
        auto path8 = std::make_shared<PathNode>(8, "path", GridPosition(6, 20));
        auto path9 = std::make_shared<PathNode>(9, "path", GridPosition(6, 23));
        auto path10 = std::make_shared<PathNode>(10, "path", GridPosition(14, 23));
        auto base = std::make_shared<PathNode>(11, "base", GridPosition(14, 24));

        // Add nodes to level
        level->addNode(spawn);
        level->addNode(path1);
        level->addNode(path2);
        level->addNode(path3);
        level->addNode(path4);
        level->addNode(path5);
        level->addNode(path6);
        level->addNode(path7);
        level->addNode(path8);
        level->addNode(path9);
        level->addNode(path10);
        level->addNode(base);

        // Connect nodes
        Level::connectNodes(spawn, path1);
        Level::connectNodes(path1, path2);
        Level::connectNodes(path2, path3);
        Level::connectNodes(path3, path4);
        Level::connectNodes(path4, path5);
        Level::connectNodes(path5, path6);
        Level::connectNodes(path6, path7);
        Level::connectNodes(path7, path8);
        Level::connectNodes(path8, path9);
        Level::connectNodes(path9, path10);
        Level::connectNodes(path10, base);

        // Add tower spots adjacent to path
        level->addTowerSpot(GridPosition(3, 4).toPixelPosition());
        level->addTowerSpot(GridPosition(5, 7).toPixelPosition());
        level->addTowerSpot(GridPosition(9, 9).toPixelPosition());
        level->addTowerSpot(GridPosition(5, 14).toPixelPosition());
        level->addTowerSpot(GridPosition(8, 17).toPixelPosition());
        level->addTowerSpot(GridPosition(13, 18).toPixelPosition());
        level->addTowerSpot(GridPosition(7, 21).toPixelPosition());
        level->addTowerSpot(GridPosition(10, 21).toPixelPosition());
        level->addTowerSpot(GridPosition(13, 22).toPixelPosition());
        level->addTowerSpot(GridPosition(7, 24).toPixelPosition());
    }

    static void configureLevelTwo(const std::shared_ptr<Level>& level) {
        // Create nodes with path covering the map (16 width, 26 height)
        auto spawn = std::make_shared<PathNode>(0, "spawn", GridPosition(3, 1));
        auto path1 = std::make_shared<PathNode>(1, "path", GridPosition(3, 8));
        auto path2 = std::make_shared<PathNode>(2, "path", GridPosition(10, 8));
        auto path3 = std::make_shared<PathNode>(3, "path", GridPosition(10, 4));
        auto path4 = std::make_shared<PathNode>(4, "path", GridPosition(13, 4));
        auto path5 = std::make_shared<PathNode>(5, "path", GridPosition(13, 14));
        auto path6 = std::make_shared<PathNode>(6, "path", GridPosition(6, 14));
        auto path7 = std::make_shared<PathNode>(7, "path", GridPosition(6, 19));
        auto path8 = std::make_shared<PathNode>(8, "path", GridPosition(14, 19));
        auto path9 = std::make_shared<PathNode>(9, "path", GridPosition(14, 25));
        auto base = std::make_shared<PathNode>(10, "base", GridPosition(8, 26));

        // Add nodes to level
        level->addNode(spawn);
        level->addNode(path1);
        level->addNode(path2);
        level->addNode(path3);
        level->addNode(path4);
        level->addNode(path5);
        level->addNode(path6);
        level->addNode(path7);
        level->addNode(path8);
        level->addNode(path9);
        level->addNode(base);

        // Connect nodes
        Level::connectNodes(spawn, path1);
        Level::connectNodes(path1, path2);
        Level::connectNodes(path2, path3);
        Level::connectNodes(path3, path4);
        Level::connectNodes(path4, path5);
        Level::connectNodes(path5, path6);
        Level::connectNodes(path6, path7);
        Level::connectNodes(path7, path8);
        Level::connectNodes(path8, path9);
        Level::connectNodes(path9, base);

        // Add tower spots adjacent to path
        level->addTowerSpot(GridPosition(4, 5).toPixelPosition());
        level->addTowerSpot(GridPosition(7, 9).toPixelPosition());
        level->addTowerSpot(GridPosition(11, 6).toPixelPosition());
        level->addTowerSpot(GridPosition(14, 8).toPixelPosition());
        level->addTowerSpot(GridPosition(9, 15).toPixelPosition());
        level->addTowerSpot(GridPosition(5, 16).toPixelPosition());
        level->addTowerSpot(GridPosition(11, 18).toPixelPosition());
        level->addTowerSpot(GridPosition(15, 20).toPixelPosition());
        level->addTowerSpot(GridPosition(13, 23).toPixelPosition());
    }
};

#endif //LEVELLOADER_H