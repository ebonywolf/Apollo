/*
 * Renderer.h
 *
 *  Created on: 22 de jul de 2019
 *      Author: wagner
 */

#ifndef RENDERER_H_
#define RENDERER_H_
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Event.hpp>

#include "Position.h"
#include <memory>
#include <list>
#include <thread>
namespace pg
{
using Spriteptr = std::shared_ptr<sf::Shape>;

struct Renderer
{
    Renderer(pg::Position size);
    sf::RenderWindow* window;
    void begin();
    void beginAssync();
    void add( Spriteptr);
    std::list<std::weak_ptr<sf::Shape>> sprites;
    std::thread* assync = 0;
    void onEvent( sf::Event event);

    bool running = false;
};

} /* namespace pg */

#endif /* RENDERER_H_ */
