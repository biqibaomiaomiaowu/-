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
	int getx();
	int gety();
	bool getskill_tracebullet();
	bool getskill_bigbullet();
	bool getskill_circlebullet();
	void changeskill_tracebullet();
	void changeskill_bigbullet();
	void changeskill_circlebullet();
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
	int gamecont = 0;
	int playframerate = 2;//动画播放帧率=游戏帧率(gameframerate)/playframerate
	bool skill_tracebullet=false;
	bool skill_bigbullet = false;
	bool skill_circlebullet = false;
};

