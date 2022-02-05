#pragma once
#include <iostream>
#include <random>
#include <vector>

/**
 *The struct defines a rectangle
 */
struct Rectang {
    int width, height, x, y;

    /**
    * collision detection between rectangles
    * @param other is the collided rectangle.
    * @return true if any side of the rectangle collided with another rectangle
    * otherwise it reurns false
    */
    //https://medium.com/@hemalatha.psna/collision-detection-in-javascript-efafe8bba2c0
    bool intersects(Rectang other) {
        if (x + width >= other.x &&
            other.x + other.width >= x &&
            y + height >= other.y &&
            other.y + other.height >= y) {
            return true;
        }
        return false;
    }
};
