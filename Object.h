/*
 * Object.h
 *
 *  Created on: 22 de jul de 2019
 *      Author: wagner
 */

#ifndef OBJECT_H_
#define OBJECT_H_
#include <ProjGaia/Tools/Coord.h>

#include <SFML/Graphics.hpp>
namespace pg
{

class Object: public Coord
{
    Object(sf::Drawable* drawable);
    ~Object(){

    }
    sf::Drawable* drawable;


};

} /* namespace pg */

#endif /* OBJECT_H_ */
