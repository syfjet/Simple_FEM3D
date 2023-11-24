#pragma once
#include <iostream>
#include <vector>
#include <array>

class Object{
public:
	class Node
	{
	public:
		int part = 0;
		std::array<double,3> coordinate = {0,0,0};	
		std::vector<int> connection;	
		std::array<double,3> force = {0};
		std::array<double,3> displacement = {0};			
	protected:
	private:				
	}; 

	class Segment
	{
	public:
		int part = 0;
		std::array<int,3> index_node;	
		int type = 0;
		double area;
	protected:
	private:					
	};  

	class Cell
	{
	public:
		int part = 0;
		std::array<int,4> index_node;	
		double volume = 0;

		double E = 0;
		double nu = 0;
		
		std::array<std::array<double,12>,6> B_matrix = {{0}};  
		std::array<std::array<double,12>,12> local_K_matrix = {{0}};

		std::array<double,6> epsilon = {{0}};
		std::array<double,6> stress = {{0}};
		double full_stress = 0;
	};
	std::vector<Node> node;			
	std::vector<Segment> segment;	
	std::vector<Cell> cell;
};


 