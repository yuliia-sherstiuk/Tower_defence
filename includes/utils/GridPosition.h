//
// Created by chris on 05/06/2025.
//

#ifndef GRIDPOSITION_H
#define GRIDPOSITION_H

#include "../utils/Position.h"

//Grid position structure
struct GridPosition {
    int row;
    int col;
    static constexpr int CELL_SIZE = 60;

    explicit GridPosition(int r = 0, int c = 0) : row(r), col(c) {}

    Position toPixelPosition() const {
        return Position(static_cast<float>(col * CELL_SIZE),
                       static_cast<float>(row * CELL_SIZE));
    }

    //Grid pos from pix pos
    static GridPosition fromPixelPosition(const Position& pos) {
        return GridPosition(static_cast<int>(pos.y / CELL_SIZE),
                          static_cast<int>(pos.x / CELL_SIZE));
    }

    // Add comparison operator
    bool operator==(const GridPosition& other) const {
        return row == other.row && col == other.col;
    }

    //Add operator !=
    bool operator!=(const GridPosition& other) const {
        return !(*this == other);
    }
};

#endif //GRIDPOSITION_H
