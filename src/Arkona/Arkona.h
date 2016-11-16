#include <vector>
#include <SFML/Graphics.hpp>

#ifndef ARKONA_H_INCLUDED
#define ARKONA_H_INCLUDED

namespace ar{
    /**
    * distanceBetweenVector2f- returns float
    *
    * As arguments it takes two sf::Vector2f
    * Example:
    *   distanceBetweenVector2f(playerPos,enemyPos);
    * where playerPos and enemy pos are sf::Vector2f variables
    */
    float distanceBetweenVector2f(sf::Vector2f first, sf::Vector2f second);


    //! return opposite number

    float getOppositeNumber(float number);

    //! Structure based on linear equation

    //! contain two variables
    //!
    struct linear_equation{
        float a;
        float b;
    };

    /* funkcja zwracajaca rownanie liniowe
    przechodzace przez dwa podane Vectory2f
    */
    linear_equation getLinePassingVectors2f(sf::Vector2f first, sf::Vector2f second);

    /* zwraca linie przechodzaca przez
    oba wskazane wie*/

    //! check is collision between two rectangles

    //! return bool value

    bool isCollisionBetweeenRectangles(sf::RectangleShape rectangle_one, sf::RectangleShape rectangle_two);

    bool isRectangleInsideRectangle(sf::RectangleShape rectangle_one, sf::RectangleShape rectangle_two);

    bool isCollisionBetweenPointAndRectangle(sf::Vector2f point, sf::RectangleShape rectangle);

}

#endif // ARKONA_H_INCLUDED
