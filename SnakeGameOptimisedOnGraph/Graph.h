#pragma once
#include "Node.h"
#include <vector>
#include <unordered_map>

class Graph 
{
private:
	std::vector<Node*> nodes;  // this vectors saves all the nodes in the graph we are going to generate

																  //====================================================================//
	std::unordered_map<int, std::vector<Node*>> neighboor_nodes; //this map completes the graph logic of the game  (undirected graph),it connects every node of the graph with its neighboors
																//====================================================================//
public:
	Graph();
	~Graph();

	void generateGrid(int rows, int columns);  //creates grid
	void draw();							   //draws the nodes and the lines connecting them
	Node* getNode(int id);
	Node* getNeighboorDirection(Node* current, char direction); //core movement method
	void spawnFood(); //generates the apples
	
};


