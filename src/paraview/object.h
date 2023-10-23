#pragma once
#include <iostream>
#include <vector>
#include <array>
using namespace std; 

class Object{
public:
	class Node
	{
	public:
		int part = 0;
		array<double,3> coordinate = {0,0,0};	
		vector<int> connection;	
		array<double,3> force = {0};
		array<double,3> displacement = {0};			
	protected:
	private:				
	}; 

	class Segment
	{
	public:
		int cell = 0;
		int part = 0;
		array<int,3> index_node;	
		int type = 0;
		double area;
	protected:
	private:					
	};  

	class Cell
	{
	public:
		int part = 0;
		array<int,4> index_node;	
		array<int,4> connection = {-1,-1,-1,-1};
		double volume = 0;


		double E = 0;
		double nu = 0;
		
		array<array<double,12>,6> B_matrix = {{0}};  
		array<array<double,12>,12> local_K_matrix = {{0}};

		array<double,6> epsilon = {0,0,0,0,0,0};
		array<double,6> stress = {0,0,0,0,0,0};
		double full_stress = 0;
	};
	vector<Node> node;			
	vector<Segment> segment;	
	vector<Cell> cell;
};


 