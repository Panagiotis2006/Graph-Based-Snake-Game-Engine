#include "Snake.h"
#include "sgg/graphics.h"
#include "Node.h"
#include "Util.h"
Node* Snake::getHead() 
{
	return m_body.front();
}
void Snake::draw()
{
	for (Node* n : m_body)
	{
		graphics::Brush snake_br;
		SETCOLOR(snake_br.fill_color, 0.0f, 1.0f, 0.0f); //green
		graphics::drawRect(n->x, n->y, 0.9f, 0.9f, snake_br);
	}
}
void Snake::move(Node* next_Node, bool grow)
{
	if (next_Node == nullptr)
	{
		return;
	}
	m_body.push_front(next_Node);
	if (!grow)
	{
		m_body.pop_back(); 
	}
}
bool Snake::containsNode(Node* n)			//elegxos an to node n pou dothike anikei sto swma tou fidiou
{
	for (Node* segment : m_body)
	{
		if (segment == n) return true;
	}
	return false;
}
