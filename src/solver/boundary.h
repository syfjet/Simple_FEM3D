#pragma once
#include "../object.h"

template<class O>
class Boundary
{	
	public:
		Boundary();
		~Boundary();
	protected:
	template<class V> void boundary_set(O &obj,V &global_force);
	private:
}; 

 
 
