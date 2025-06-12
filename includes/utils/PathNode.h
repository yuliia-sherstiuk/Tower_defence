//
// Created by chris on 04/06/2025.
//

#ifndef PATHNODE_H
#define PATHNODE_H

#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include "utils/Position.h"
#include "utils/GridPosition.h"

class PathNode {
private:
    int id;
    std::string type; //"spawn", "path", "base", "tower_spot"
    GridPosition gridPos;
    std::vector<std::shared_ptr<PathNode>> connections;

public:
    PathNode(int id, std::string type, GridPosition pos)
        : id(id), type(std::move(type)), gridPos(pos) {}

    //Getters
    const GridPosition& getGridPosition() const { return gridPos; }
    Position getPixelPosition() const { return gridPos.toPixelPosition(); }
    int getId() const { return id; }
    const std::string& getType() const { return type; }

    //Handling connections
    void addConnection(std::shared_ptr<PathNode> node) {
        connections.push_back(std::move(node));
    }

    const std::vector<std::shared_ptr<PathNode>>& getConnections() const {
        return connections;
    }

    // Find next node
    std::shared_ptr<PathNode> findNextNode(const std::shared_ptr<PathNode>& previousNode = nullptr) const {
        if (connections.empty()) {
            return nullptr;
        }

        if (!previousNode) {
            return connections[0];
        }

        auto it = std::find(connections.begin(), connections.end(), previousNode);
        if (it != connections.end() && std::next(it) != connections.end()) {
            return *(std::next(it));
        }

        // if current node had only one connection and if it is not the previous node, return nullptr
        if (connections.size() == 1 && connections[0] == previousNode) {
            return nullptr;
        }

        // else, return first connection that is not the previous node
        for (const auto& conn : connections) {
            if (conn != previousNode) {
                return conn;
            }
        }

        return nullptr;
    }

    bool isConnectedTo(const std::shared_ptr<PathNode>& other) const {
        return std::find(connections.begin(), connections.end(), other) != connections.end();
    }
};
#endif //PATHNODE_H