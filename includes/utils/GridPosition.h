//
// Created by chris on 05/06/2025.
//

#ifndef GRIDPOSITION_H
#define GRIDPOSITION_H

#include "Position.h"

struct GridPosition {
    int row;
    int col;
    static constexpr int CELL_SIZE = 60;

    explicit GridPosition(int r = 0, int c = 0) : row(r), col(c) {}

    Position toPixelPosition() const {
        return Position(static_cast<float>(col * CELL_SIZE),
                       static_cast<float>(row * CELL_SIZE));
    }

    static GridPosition fromPixelPosition(const Position& pos) {
        return GridPosition(static_cast<int>(pos.y / CELL_SIZE),
                          static_cast<int>(pos.x / CELL_SIZE));
    }
};

#endif //GRIDPOSITION_H
