#pragma once
#include "boundary.h"
#include "boundary.cpp"
#include "../object.h"

template<class O>
class Linalg: Boundary<O>
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

 
 
