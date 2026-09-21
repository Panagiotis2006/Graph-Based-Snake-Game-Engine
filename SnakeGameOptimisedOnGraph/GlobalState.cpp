#include "GlobalState.h"
#include "Graph.h"
#include "sgg/graphics.h"
#include <iostream>
#include "Util.h"

GlobalState* GlobalState::m_Instance = nullptr;
GlobalState::GlobalState() 
{
	m_timer = 0.0f;			
	m_delay = 0.2f;
}
GlobalState::~GlobalState()
{
	delete snake;
	delete graph;
}

Graph* GlobalState::getGraph()
{
	return graph;
}

GlobalState* GlobalState::getInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new GlobalState;
	}
	return m_Instance;
}

void GlobalState::init()		//arxikopoihsh olwn twn ontothtwn pou ua xreiastoun
{
	graph = new Graph();
	graph->generateGrid(10, 15);		//10 grammes , 15 sthles
	graph->spawnFood();					//kane prwta generate to apple
	Node* start = graph->getNode(0);	
	snake = new Snake(start);			//jekina to fidi apo ton proto kombo tou grid kai dose axikh kateuinsi pros ta katw, DOWN
	snake_direction_move = 'D';
	last_move_direction = 'D';
}

void GlobalState::draw()
{
	if (graph != nullptr)
	{
		graph->draw();
	}

	if (snake != nullptr)
	{
		snake->draw();
	}
}

void GlobalState::update(float dt)
{

	float delta_time = dt / 1000.0f;	//metarepoume ta ms se s 
	m_timer += delta_time;


	if (graphics::getKeyState(graphics::SCANCODE_A) && last_move_direction!= 'R')		//edo elegxoume wste o xristis na mhn mporei na paei sthn antitheti poreia apoti pigaine
	{
		snake_direction_move = 'L';
	}
	if (graphics::getKeyState(graphics::SCANCODE_D) && last_move_direction != 'L')
	{
		snake_direction_move = 'R';
	}
	if (graphics::getKeyState(graphics::SCANCODE_W) && last_move_direction != 'D')
	{
		snake_direction_move = 'U';
	}
	if (graphics::getKeyState(graphics::SCANCODE_S) && last_move_direction != 'U')
	{
		snake_direction_move = 'D';
	}

	if (m_game_over == true)		
	{
		if (graphics::getKeyState(graphics::SCANCODE_R))
		{
			reset();
		}
		if (graphics::getKeyState(graphics::SCANCODE_E))
		{
			graphics::stopMessageLoop();
		}
		return;
	}

	if (m_timer > m_delay)			//an to timer jeperase to delay tote jekina pali ton ktipo tou paixnidiou, etsi to painxdi trehei me tin idia taxithta se kathe
	{							   // ypologisth xvris na paizei rolo h taxitita ths CPU
		m_timer = 0;
		last_move_direction = snake_direction_move;

		if (snake != nullptr)
		{
			Node* head = snake->getHead();
			Node* next = graph->getNeighboorDirection(head, last_move_direction);

			//kritirio termatismou 1

			if (next == nullptr || next->is_Walkable() == false)
			{
				if (!m_game_over) { 
					std::cout << "\n===========================================" << std::endl;
					std::cout << "   GAME OVER: Hit an Obstacle! " << std::endl;
					std::cout << "   Final Score: " << m_score << std::endl;
					std::cout << "   Press R to Restart or E to Exit" << std::endl;
					std::cout << "===========================================\n" << std::endl;
				}
				m_game_over = true;
				return;
			}

			//kritirio termatismou 2


			if (snake->containsNode(next) == true)
			{
				if (!m_game_over) { 
					std::cout << "\n===========================================" << std::endl;
					std::cout << "   GAME OVER: Bit Yourself!    " << std::endl;
					std::cout << "   Final Score: " << m_score << std::endl;
					std::cout << "   Press R to Restart or E to Exit" << std::endl;
					std::cout << "===========================================\n" << std::endl;
				}
				m_game_over = true;
				return;
			}

			if (next->type == FOOD)		//an to type tou kombou einai food tote 1)auksise to score 2)kane to kombo food aplo kombo grid 3) steile true sto move wste na megalswsei to fifi kai kane pali spawn to apple
			{
				m_score += 10;
				next->type = GRID;
				snake->move(next, true); 
				graph->spawnFood();
			}

					//aliws apla epetrepse tin kinisi
			else
			{
				snake->move(next, false); 
			}
		}
	}
}

Snake* GlobalState::getSnake()
{
	return snake;
}
									// an o xristis xasei kai zitisei na jana paixei tote sbise olous tous trexon deiktes kai jana arxikopoihse tous ws null gia na einai etoimoi pros arxikopoihsh apo thn klisi ths init()
void GlobalState::reset()
{
	if (graph != nullptr) 
	{
		delete graph;
		graph = nullptr;
	}
	if (snake != nullptr)
	{
		delete snake;
		snake = nullptr;
	}
	m_game_over = false;
	m_score = 0;
	init();
	std::cout << "GAME RESTARTED!" << std::endl;
}
