#include "Arkona/Arkona.h"
#include <SFML/System/Vector2.hpp>
#include <math.h>

float ar::distanceBetweenVector2f(sf::Vector2f first,sf::Vector2f second){
    float one_part = 0;
    float second_part = 0;
    float result = 0;

    one_part = second.x - first.x;
    one_part *= one_part;
    second_part = second.y - first.y;
    second_part *= second_part;

    result = sqrt(one_part + second_part);

    return result;
}

float ar::getOppositeNumber(float number){
    return pow(number, -1);
}

ar::linear_equation ar::getLinePassingVectors2f(sf::Vector2f first, sf::Vector2f second){
    ar::linear_equation result_line;
    result_line.a = 0.f;
    result_line.b = 0.f;

    result_line.a = (first.y - second.y) / (first.x - second.x);
    result_line.b = first.y - result_line.a * first.y;

    return result_line;
}

bool ar::isCollisionBetweeenRectangles(sf::RectangleShape rectangle_one, sf::RectangleShape rectangle_two){
        sf::Vector2f position1 = rectangle_one.getPosition();
        sf::Vector2f position2 = rectangle_two.getPosition();

        if(position1.x > position2.x + rectangle_two.getSize().x ||
           position2.x > position1.x + rectangle_one.getSize().x ||
           position1.y > position2.y + rectangle_two.getSize().y ||
           position2.y > position1.y + rectangle_one.getSize().y ){
                return false;
           }
        else{
            return true;
        }
}

//! check is first one rectangle inside second one

bool ar::isRectangleInsideRectangle(sf::RectangleShape rectangle_one, sf::RectangleShape rectangle_two){
    sf::Vector2f position1_start = rectangle_one.getPosition();
    sf::Vector2f position1_end(position1_start.x + rectangle_one.getSize().x, position1_start.y + rectangle_one.getSize().y);
    sf::Vector2f position2_start = rectangle_two.getPosition();
    sf::Vector2f position2_end(position2_start.x + rectangle_two.getSize().x, position2_start.y + rectangle_two.getSize().y);

    if(position1_start.x >= position2_start.x && position1_start.y >= position2_start.y &&
        position1_end.x <= position2_end.x && position1_end.y <= position2_end.y){
            return true;
    }
    else{
            return false;
    }

}


bool ar::isCollisionBetweenPointAndRectangle(sf::Vector2f point, sf::RectangleShape rectangle_one){
    sf::Vector2f position1_start = rectangle_one.getPosition();
    sf::Vector2f position1_end(position1_start.x + rectangle_one.getSize().x, position1_start.y + rectangle_one.getSize().y);

	if (point.x >= position1_start.x && point.x <= position1_start.x + rectangle_one.getSize().x &&
		point.y >= position1_start.y && point.y <= position1_start.y + rectangle_one.getSize().y)
		return true;

	else
		return false;
}
