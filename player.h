#pragma once
#include<easyx.h>
#include<iostream>
class Player
{
public:
	void init();
	void draw();
	void move();
	void putimagePNG(int x, int y, IMAGE* picture);
private:
	IMAGE player[31];
	int x=450;
	int y=450;
	int imagenub = 0;
	bool up=false;
	bool down=false;
	bool left=false;
	bool right=false;
	int speed = 5;
};

