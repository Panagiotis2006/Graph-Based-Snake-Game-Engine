#pragma once

#include "sgg/graphics.h"
#include "Node.h"
#include <deque>

class Snake
{
private:
	std::deque<Node*> m_body;			//apothikeuoume to swma tou fidiou se mia deque kai oxi px se list h' vecotr kathos oi praxeis se deque einai O(1)
public:
	Snake(Node* startNode)
	{
		m_body.push_back(startNode);		//me to pou dhmiourgithi to fidi ftiaxnoume to kefali tou fidiou
	}
	void draw();
	void move(Node* nextNode, bool grow);
	Node* getHead();
	bool containsNode(Node* n);
};