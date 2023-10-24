#pragma once
#include "shift.h"

#include "../object.h"

template<class O>
class Stress_value: virtual Shift<O>
{	
	public:
		Stress_value();
		~Stress_value();
	protected:
		void define_stress_values(O &obj);
	private:
		template<class I> void epsilon(I i,O &obj);
		template<class I> void stress(I i,O &obj);
}; 

 
 
