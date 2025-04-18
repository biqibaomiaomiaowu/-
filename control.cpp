#include "control.h"
void Control::init()
{
    map->init();
    player->init();

}
Control::Control(Map* map, Player* player)
{
    this->map = map;
    this->player = player;

}
