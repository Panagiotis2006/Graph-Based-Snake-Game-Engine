#pragma once

enum NodeType {GRID, FOOD, OBSTACLE}; //creating data type enumerator for the types of nodes instead of creating 3 classes GridNode-FoodNode-ObstacleNode

class Node
{
public:
	float x; //coordinates
	float y;
	int id;
	NodeType type;

	Node(float new_x, float new_y, int new_id, NodeType new_type) : x(new_x), y(new_y), id(new_id), type(new_type) 
    {}
	virtual ~Node() = default;			 // making the Node class
	virtual void draw() = 0;		    //        abstract
	virtual bool is_Walkable() = 0;
};

class GridNode :public Node				//GridNode inherits from Node and overrides its method through polymorphism
{
public:
	GridNode(float x, float y, int id, NodeType type = GRID): Node(x,y,id,type)
	{}
	void draw() override;
	bool is_Walkable() override;

};
