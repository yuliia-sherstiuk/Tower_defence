//
// Created by chris on 04/06/2025.
//
#ifndef PATHNODE_H
#define PATHNODE_H

#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include "Position.h"
#include "GridPosition.h"

class PathNode {
private:
    int id;
    std::string type; //"spawn", "path", "base", "tower_spot"
    GridPosition gridPos;
    std::vector<std::shared_ptr<PathNode>> connections;

public:
    PathNode(int id, std::string type, GridPosition pos)
        : id(id), type(std::move(type)), gridPos(pos) {}

    const GridPosition& getGridPosition() const { return gridPos; }
    Position getPixelPosition() const { return gridPos.toPixelPosition(); }

    //Getters
    int getId() const { return id; }
    const std::string& getType() const { return type; }

    //Handling connections
    void addConnection(std::shared_ptr<PathNode> node) {
        connections.push_back(std::move(node));
    }

    const std::vector<std::shared_ptr<PathNode>>& getConnections() const {
        return connections;
    }

    std::shared_ptr<PathNode> findNextNode(const std::shared_ptr<PathNode>& previousNode = nullptr) const {
        if (!previousNode && !connections.empty()) {
            return connections[0];
        }

        for (size_t i = 0; i < connections.size(); ++i) {
            if (connections[i] == previousNode && i + 1 < connections.size()) {
                return connections[i + 1];
            }
        }
        return nullptr;
    }

    bool isConnectedTo(const std::shared_ptr<PathNode>& other) const {
        return std::find(connections.begin(), connections.end(), other) != connections.end();
    }
};
#endif //PATHNODE_H