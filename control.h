#pragma once
#include"enemy.h"
#include"player.h"
#include"map.h"
#include"Orzbie.h"
class Control
{public:
	void init();
	Control(Map * map, Player* player);
private:
	Map * map;
    Player * player;
    Enemy * enemy;
};

