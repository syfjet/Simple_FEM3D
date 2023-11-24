#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include "../object.h"

template<class O>
class Out
{	
public:
	Out();
	~Out();
protected:
	void out_paraview(O &obj);
private:
};
