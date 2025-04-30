#pragma once
#include<easyx.h>
#include<time.h>
#include<iostream>
#include<random>
class Nbzombie
{
public:
	Nbzombie(int bulletATK);
	void move();
	void draw();
	void putimagePNG(int x, int y, IMAGE* picture);
	void zombieposition();
	int getx();
	int gety();
	void getattack();
	int getHP();
	void HPdown();
private:
	int x = 1110;
	int y = 0;
	int speed = 2;
	int bulletATK = 1;
	IMAGE nbzombies[54];
	int imagenub = 0;
	int playframerate = 5;
	int gamecont = 0;
	int HP = 4;
};

