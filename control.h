#pragma once
#include"enemy.h"
#include"player.h"
#include"map.h"
class Control
{public:
	void init();
	Control(Map * map, Player* player, Enemy* enemy);
private:
	Map * map;
    Player * player;
    Enemy * enemy;
};

