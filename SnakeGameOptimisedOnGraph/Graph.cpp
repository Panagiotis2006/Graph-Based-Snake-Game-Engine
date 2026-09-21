#include  "sgg/graphics.h"
#include "Graph.h"
#include "Node.h"
#include "Util.h"
#include <cstdlib>
#include "Snake.h"
#include "GlobalState.h"

Graph::Graph() {};
Graph::~Graph() //cleaning memory 
{
	for (Node* n : nodes)
	{
		delete n;
	}
}

void Graph::generateGrid(int rows, int columns)
{	
	for (int i = 0; i < rows; i++) 
	{
		for (int j = 0; j < columns; j++) 
		{
			float x = j + 1.0f; // +1.0f is important for correct spacing between nodes
			float y = i + 1.0f;
			int id = i * columns +j;  // grammiki anathesi id se olous tous kombous tou grid 
			Node* n = new GridNode(x, y, id);
			nodes.push_back(n);
		}
	}
	
	// edw ylopoihtai h logikh syndeshs olwn to kombwn me tous diplanous tous (geitones)
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			int current_id = i * columns + j;
			if (j < columns - 1) { // gia na mhn dimiourgithoun grammes ektos plegmatos
				Node* n1 = getNode(current_id);
				Node* n2 = getNode(current_id + 1);
				neighboor_nodes[current_id].push_back(n2);
				neighboor_nodes[current_id + 1].push_back(n1);
			}																//amfidromi sxesi metaxi ton kombwn, o x einai geitonas me ton x.next kai o x.next me ton x
			if (i < rows - 1) { 
				Node* n1 = getNode(current_id);
				Node* n2 = getNode(current_id + columns);
				neighboor_nodes[current_id].push_back(n2);
				neighboor_nodes[current_id + columns].push_back(n1);
			}
		}
	}
}

void Graph::draw()
{
	graphics::Brush edge_b; 
	SETCOLOR(edge_b.outline_color, 0.0f, 0.5f, 0.5f);
	edge_b.outline_opacity = 1.0f;
	
	for (Node* startNode : nodes)
	{
		for (Node* neighbor : neighboor_nodes[startNode -> id])
		{
			graphics::drawLine(startNode->x, startNode->y, neighbor->x, neighbor->y, edge_b);
		}
	}
	for (Node* n : nodes)
	{
		n->draw();
	}

	//efoson exoume 2-D grafika einai simantiko na zografisoume telefteo auto pou theloume na fainetai pano pano, prota ta lines meta ta nodes
	
}

Node* Graph::getNode(int id)
{
	for (Node* n : nodes) {
		if (n->id == id) {
			return n;
		}
	}
	return nullptr;
}

Node* Graph::getNeighboorDirection(Node* current, char direction)	//edw elegxetai an  mporei to fidi na kinithei pros tin kateythinsi poy thelei o xristis
{
	if (current == nullptr) 
	{
		return nullptr;
	}
	for (Node* neighbor : neighboor_nodes[current->id])
	{
		float dx = neighbor->x - current->x;
		float dy = neighbor->y - current->y;

		if (direction == 'R' && dx > 0.0f) return neighbor;  
	    if (direction == 'L' && dx < 0.0f) return neighbor;
		if (direction == 'U' && dy < 0.0f) return neighbor;
		if (direction == 'D' && dy > 0.0f) return neighbor; 
		//o elegxos ginetai giati eno xeroume poioi einai oi geitones kai tis suntetagmenes tous den xeroume ti shetiki thesi
	}
	return nullptr;
}
void Graph::spawnFood()
{
	Snake* snake = GlobalState::getInstance()->getSnake();
	Node* target = nullptr;
	int attempts = 0;

	while (attempts < 100) {
		int random_index = rand() % nodes.size();			//simantiko gia na ginetai generate index entos tou evrous ton kombwn tou grid 
		target = nodes[random_index];

		if (target->type == GRID && (!snake || !snake->containsNode(target))) {				//prepei epishs na elegxoyme an to target den einai to kefali tou fidiou h' to swma
			target->type = FOOD;
			return; 
		}
		attempts++;
	}
}