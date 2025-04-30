#pragma once
#include"enemy.h"
#include"player.h"
#include"map.h"
#include"Orzbie.h"
#include"Bullet.h"
#include<vector>
#include <windows.h>
#include <mmsystem.h>  
#include<conio.h>
#include"Nbzombie.h"
#pragma comment(lib, "winmm.lib")
#include<math.h>
class Control
{public:
	void init();
	Control(Map * map, Player* player);
	void checkoutorzbies(std::vector < Orzbie*>& orzbies_lists, std::vector < Bullet*>& bullets_lists);
	void contactorzbies(std::vector < Orzbie*>& orzbies_lists, std::vector < Bullet*>& bullets_lists);
	void drawHP();
	void putimagePNG(int x, int y, IMAGE* picture);
	void shouscore();
	int getscore();
	void checkoutnbzombies(std::vector < Nbzombie*>& nbzombie_lists, std::vector < Bullet*>& bullets_lists);
	void contactnbzombies(std::vector < Nbzombie*>& nbzombie_lists, std::vector < Bullet*>& bullets_lists);
	void showskill();
	void drawcirclebullet();
	void contactcirclebullet(std::vector < Nbzombie*>& nbzombie_lists, std::vector < Orzbie*>& orzbies_lists);
 
        
 


    
private:
	IMAGE skill_tracebullet;
	IMAGE skill_bigbullet;
	IMAGE skill_circlebullet;
	IMAGE brain;
	Map * map;
    Player * player;
	bool playbulletsound1=false;
	int HP = 3;
	int score = 0;
	int circlebullet[3][2] = { 0 };
	int circlebulletcoolcont = 0;
	
};

