//
// Created by chris on 04/06/2025.
//

#ifndef POSITION_H
#define POSITION_H

#include <cmath>

class Position {
public:
    explicit Position(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    Position operator+(const Position& other) const {
        return Position(x + other.x, y + other.y);
    }

    Position operator-(const Position& other) const {
        return Position(x - other.x, y - other.y);
    }

    Position operator*(float scalar) const {
        return Position(x * scalar, y * scalar);
    }

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }

    float distance(const Position& other) const {
        float dx = x - other.x;
        float dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    float x;
    float y;
};

#endif //POSITION_H