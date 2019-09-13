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

#include "Coord.h"
#include "Templates.h"
#include <memory>
#include <list>
#include <thread>
namespace pg
{

using Spriteptr = std::shared_ptr<sf::Shape>;

class Renderer :  public CommandOriented, public Singleton<Renderer>
{
public:
    Renderer();
    Renderer(pg::Coord size);
     void begin();
    void beginAssync();
    void add( Spriteptr);

    virtual void update( CommandOriented::Negaptr sender ){

    }
    virtual void ack( CommandOriented::Negaptr sender , Commands cmd ){

    }
    virtual void create( CommandOriented::Negaptr sender ){

    }
    virtual void destroy( CommandOriented::Negaptr sender ){

    }


private:
    sf::RenderWindow* window;
    std::list<std::weak_ptr<sf::Shape>> sprites;
    std::thread* assync = 0;
    void onEvent( sf::Event event);
    bool running = false;

    struct Border{
        Coord min,max;
    };

};

} /* namespace pg */

#endif /* RENDERER_H_ */
