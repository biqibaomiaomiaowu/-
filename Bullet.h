#pragma once
#include<easyx.h>
#include<iostream>
#include"player.h"
#include<vector>
#include"Nbzombie.h"
#include"Orzbie.h"

class Bullet
{
public:
	Bullet(Player * player);
	void draw();
	void move();
	
	void putimagePNG(int x, int y, IMAGE* picture);
	int getx();
	int gety();
    int getATK();
	void skill_trace_orzbie_bullet(std::vector < Orzbie*>& orzbies_lists);
	void skill_trace_nbzombie_bullet(std::vector < Nbzombie*>nbzombie_lists);
private:
	IMAGE bullet[2];
	bool skill_bigbullet=false;
	IMAGE bigbullet[2];
	int x=0;
	int y=0;
	Player * player;
	int imagenub = 0;
	int speed = 5;
	int gamecont = 0;
	int playframerate = 2;
	int ATK = 1;
};

