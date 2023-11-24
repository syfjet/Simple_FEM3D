#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <regex>
#include "../object.h"

class Construction_mesh 
{
public:
	Construction_mesh();
	~Construction_mesh();
protected:
	void node_connection(Object &obj);		
	void bound_construct(Object &obj);		
private:
}; 
 