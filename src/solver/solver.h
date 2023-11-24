#pragma once
#include "../object.h"

#include "shift.h"
#include "shift.cpp"

#include "stress_value.h"
#include "stress_value.cpp"

#include "linalg.h"
#include "linalg.cpp"

#include "../paraview/out.h"
#include "../paraview/out.cpp"

template<class O>
class Solver: virtual Shift<O>, virtual Linalg<O>, Stress_value<O>, Out<O>
{	
public:
	Solver();
	~Solver();
	void FEM_solver(O &obj);
protected:
private:

};
