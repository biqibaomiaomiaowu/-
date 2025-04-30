#pragma once
#include<easyx.h>
#include<iostream>
#include<time.h>
#include<random>
class Orzbie
{
public:
	Orzbie(int bulletATK);
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
	int bulletATK = 1;
	int x = 1110;
	int y=0;
	int speed = 1;
	IMAGE zombies[10];
	int imagenub = 0;
	int playframerate = 5;
	int gamecont = 0;
	int HP = 2;
};

