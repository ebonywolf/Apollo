/*
 * Renderer.cpp
 *
 *  Created on: 22 de jul de 2019
 *      Author: wagner
 */

#include "Renderer.h"

namespace pg
{

Renderer::Renderer(Coord size):window()
{
    window = new   sf::RenderWindow(sf::VideoMode(size.x,size.y), "My window");
}


void  Renderer::add( Spriteptr pt)
{
    sprites.push_back( pt  );
}
void Renderer::onEvent( sf::Event event)
{

    if (event.type == sf::Event::Closed){
        window->close();
        running= false;
    }


}
void Renderer::begin()
{

    window->setActive(true);
    while (window->isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window->pollEvent(event)) {
            // "close requested" event: we close the window
            onEvent(event);
        }
        // clear the window with black color
        window->clear(sf::Color::Black);
        for (auto i = sprites.begin(); i != sprites.end();) {
            auto& ptr = *i;
            if (ptr.expired())
                i = sprites.erase(i);
            else {
                auto drawable = ptr.lock();
                window->draw(*drawable.get() );

                ++i;
            }
        }
        window->display();
        //  std::this_thread::sleep_for ( std::chrono::milliseconds ( 16 ) );
    }
}
void Renderer::beginAssync()
{
    auto func = [this]() {
        this->begin();
    };
    window->setActive(false);
    assync = new std::thread ( func );
    assync->detach();
}



// run the program as long as the window is open

}
