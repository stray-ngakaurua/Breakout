#pragma once
#include "rect.h"
#include "constants.h"
#include "SFML/Graphics.hpp"


/**
*The struct defines the ball we use to play in order to smash the bricks
* 
*/
struct BouncingBall {

    int x = screenWidth / 2;
    int y = screenHeight / 2;
    int vx = 15;
    int vy = 15;
    sf::CircleShape shape;
    
    /**
    * updating the direction of the ball when it collides with the walls, floor and the ceiling 
    */
    void updateBall() {
        x += vx;
        y += vy;
        
        if (x < 0) {
            x -= vx;
            vx = -vx;
        }
        
        if (x + shape.getRadius() * 2 > screenWidth) {
            x -= vx;
            vx = -vx;
        }
        
        if (y < -1) {
            y -= vy;
            vy = -vy;
        }
       
        if (y + shape.getRadius() * 2 > screenHeight) { 
           
            vy = -vy;
        }
        //The position of the ball sets after calculating the new position 
        shape.setPosition(x, y);
    }

   /**
   *displaying the ball
   *
   */
    void draw(sf::RenderWindow &window) {
        window.draw(shape);
    }

    /**
    *defining the position, color and radius for the ball
    *
    */
    BouncingBall() {
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::White);;
        shape.setRadius(10);
    }


        /**
       * checks collision between ball and rectangles
       * @param rectangle is the rectangle that is needed to be checked
       * @return true if the rectangle has hit by the ball
       */
    bool intersects(Rectang rectangle) {
        Rectang hitBox;
        hitBox.x = x;
        hitBox.y = y;
        hitBox.height = shape.getRadius() * 2;
        hitBox.width = shape.getRadius() * 2;
        return hitBox.intersects(rectangle);

    }

};
