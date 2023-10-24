#pragma once
#include <iostream>
#include <cmath>
#include <array>
#include <vector>
#include "../object.h"
#include "geometry.h"
#include "linalg.h"
using namespace std; 
template<class O>
class Shift: Geometry, virtual Linalg<O>
{	
	public:
		Shift();
		~Shift();
		void define_matrix(O &obj); 
		array<array<double,6>,6> hooke_matrix = {{0}};
	protected:
		template<class I> void hooke(I i,O &obj);
	private:
}; 

 
 
