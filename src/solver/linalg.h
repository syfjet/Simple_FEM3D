#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include "boundary.h"

#include "../object.h"

template<class O>
class Linalg: Boundary
{	
	public:
		Linalg();
		~Linalg();
	protected:
		void solve_linear_system(O &obj);
		class K_rigid_sparse
		{	public:
			std::vector<int> index;
			std::vector<double> element; 
		};
		std::vector<K_rigid_sparse> k_rigid;
	private:
		template<class V> void update_K_rigid(V &U);
}; 

 
 
