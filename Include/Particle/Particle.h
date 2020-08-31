#ifndef PARTICLE_H
#define PARTICLE_H

#pragma once

#include "Apollo.h"





class Particle : public std::shared_ptr<pg::Process_Base>
{
public:
	std::shared_ptr<pg::Process_Base> data;

	Particle(std::shared_ptr<pg::Process_Base> ptr){
		this->data = ptr;
	}
	Particle getEntity(std::string name){
	    auto key = std::make_shared<pg::HashKey>(name);

		if( this->get()->hasOmni(key) ) {
			auto current = this->get()->getOmni(key);
			return Particle(current);
		}else{
			return 0;
		}
	}

};


#endif //PARTICLE_H
