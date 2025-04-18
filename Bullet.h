#pragma once
#include<easyx.h>
#include<iostream>
#include"player.h"
class Bullet
{
public:
	Bullet(Player * player);
	void draw();
	void contact();
	void move();IMAGE bullet[2];
	void putimagePNG(int x, int y, IMAGE* picture);
private:
	
	int x=300;
	int y=300;
	Player * player;
	int imagenub = 0;
	int speed = 5;
	int gamecont = 0;
	int playframerate = 2;
};

