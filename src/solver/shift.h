#pragma once
#include <iostream>
#include <cmath>
#include <array>
#include <vector>
#include "../object.h"
#include "geometry.h"
#include "linalg.h"
using namespace std; 
class Shift: Geometry, virtual Linalg
{	
	public:
		Shift();
		~Shift();
		void define_matrix(Object &obj); 
		array<array<double,6>,6> hooke_matrix = {{0}};
	protected:
		void hooke(int i,Object &obj);
	private:
}; 

 
 
