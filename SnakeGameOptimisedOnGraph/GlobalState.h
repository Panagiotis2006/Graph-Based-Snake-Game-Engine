#pragma once
#include "Graph.h"
#include "Snake.h"


//singleton class

class GlobalState
{
private:
	GlobalState();
	~GlobalState();

	Graph* graph = nullptr;
	int m_score;
	static GlobalState* m_Instance;

	float m_timer;
	float m_delay;
	Snake* snake = nullptr;
	char snake_direction_move;
	char last_move_direction;
	
public:
	static GlobalState* getInstance();
	void draw();
	void update(float dt);
	void init();
	Graph* getGraph();
	Snake* getSnake();
	bool m_game_over = false;
	void reset();
};