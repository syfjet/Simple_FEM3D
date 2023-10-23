#pragma once
#include <iostream>
#include "../object.h"

#include "shift.h"
//#include "shift.cpp"

#include "stress_value.h"
//#include "stress_value.cpp"

#include "linalg.h"
#include "../paraview/out.h"


class Solver: virtual Shift, virtual Linalg, Stress_value, Out
{	
public:
	Solver();
	~Solver();
	void FEM_solver(Object &obj);
protected:
private:

};
