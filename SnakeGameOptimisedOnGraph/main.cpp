#include <iostream>
#include "sgg/graphics.h"
#include "GlobalState.h"

void draw() 
{
    GlobalState::getInstance()->draw();
}
void update(float dt) 
{
    GlobalState::getInstance()->update(dt);
}
int main()
{
    graphics::createWindow(1400, 800, "Snake Game Optimised on Graph!");        //ftiaxe to parathiro
    graphics::setCanvasSize(16.0f, 16.0f);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);  //oso kai na peirajei o xristis to parathiro esu kentrarise pali ta graphics

    std::cout << "=============================================" << std::endl;
    std::cout << "      WELCOME TO SNAKE GAME! " << std::endl;
    std::cout << "      USE W-A-S-D TO NAVIGATE" << std::endl;
    std::cout << "=============================================" << std::endl;
    GlobalState::getInstance()->init(); //enarksi
    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);
    graphics::startMessageLoop(); 
    return 0;
}
