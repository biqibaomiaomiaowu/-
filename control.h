#pragma once
#include"enemy.h"
#include"player.h"
#include"map.h"
#include"Orzbie.h"
#include"Bullet.h"
#include<vector>
class Control
{public:
	void init();
	Control(Map * map, Player* player);
	void checkout(std::vector < Orzbie*>& orzbies_lists, std::vector < Bullet*>& bullets_lists);
	void contact(std::vector < Orzbie*>& orzbies_lists, std::vector < Bullet*>& bullets_lists);
private:
	Map * map;
    Player * player;

};

