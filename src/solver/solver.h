#pragma once
#include "../object.h"

#include "shift.h"
#include "shift.cpp"

#include "stress_value.h"
#include "stress_value.cpp"

#include "linalg.h"
#include "linalg.cpp"

#include "../paraview/out.h"

template<class O>
class Solver: virtual Shift<O>, virtual Linalg<O>, Stress_value<O>, Out
{	
public:
	Solver();
	~Solver();
	void FEM_solver(O &obj);
protected:
private:

};
