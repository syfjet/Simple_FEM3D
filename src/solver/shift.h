#pragma once
#include "../object.h"
#include "geometry.h"
#include "geometry.cpp"
#include "linalg.h"

template<class O>
class Shift: Geometry<O>, virtual Linalg<O>
{	
	public:
		Shift();
		~Shift();
		void define_matrix(O &obj); 
		std::array<std::array<double,6>,6> hooke_matrix = {{0}};
	protected:
		template<class I> void hooke(I i,O &obj);
	private:
}; 

 
 
