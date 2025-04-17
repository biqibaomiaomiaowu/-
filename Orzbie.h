#pragma once
#include<easyx.h>
#include<iostream>
#include<time.h>
#include<random>
class Orzbie
{
public:
	Orzbie();
	void move();
	void draw(); 
	void putimagePNG(int x, int y, IMAGE* picture);
	void zombieposition();
private:
	int x = 1110;
	int y=0;
	int speed = 1;
	IMAGE zombies[10];
	int imagenub = 0;
	int playframerate = 5;
	int gamecont = 0;
};

