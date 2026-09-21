#include "Node.h"
#include "sgg/graphics.h"
#include "Util.h"

void GridNode::draw()  
{
    graphics::Brush br;

    if (type == FOOD) {
        SETCOLOR(br.fill_color, 1.0f, 0.0f, 0.0f); //red
    }
    else if (type == OBSTACLE) {
        SETCOLOR(br.fill_color, 0.0f, 0.5f, 0.5f); //yellow
    }
    else {
        SETCOLOR(br.fill_color, 0.5f, 0.5f, 0.5f); //grey
    }

    br.outline_opacity = 0.5f; // semi hiding the white colour of the OUT-LINE of the rectangular
    graphics::drawRect(x, y, 0.8f, 0.8f, br);
}

bool GridNode::is_Walkable() //checks if the next node to move is rideable
{
    if (type != OBSTACLE) {
        return true;
    }
    return false;
}