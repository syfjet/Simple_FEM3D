#pragma once
#include <iostream>
#include <cmath>
#include <array>
#include "../object.h"

template<class O>
class Geometry
{	
	public:
		Geometry();
		~Geometry();
	protected:
	template<class I> 	void geometry_area(I i, O &obj);
	template<class I> 	void geometry_b_matrix(I i, O &obj);
	private:
		std::array<double,8> B = {0,0,0,0,0,0,0,0};
    	std::array<double,8> C = {0,0,0,0,0,0,0,0};
    	std::array<double,8> D = {0,0,0,0,0,0,0,0};
}; 

 
 
