#include "control.h"
void Control::init()
{
    map->init();
    player->init();
}
Control::Control(Map* map, Player* player, Enemy* enemy)
{
    this->map = map;
    this->player = player;
    this->enemy = enemy;
}
