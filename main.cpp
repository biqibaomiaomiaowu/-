#include<iostream>
#include"control.h"
#include<time.h>
#include"Orzbie.h"
#include<vector>
using namespace std;
int gameframerate = 60;
int contofozombies = 0;
int rateofozombies = 100;
int contbullet = 0;
int ratebullet = 50;
int contofnbzombies = 0;
int rateofnbzombies = 100;
clock_t gametime =0;
int stage = 1;

void getozombies(vector < Orzbie*> &orzbies_lists) 
{
	contofozombies++;
	if (contofozombies >= rateofozombies) 
	{
		orzbies_lists.push_back(new Orzbie());
		contofozombies = 0;
	}
}

void getfierbullet(vector < Bullet*>& fierbullet_lists,Player *player) 
{
	contbullet++;
	if (contbullet >= ratebullet) {
		fierbullet_lists.push_back(new Bullet(player));
		contbullet = 0;
	}
}
void getnbzombie(vector < Nbzombie*>&nbzombie_lists)
{
    	contofnbzombies++;
        	if (contofnbzombies >= rateofnbzombies) {
            		nbzombie_lists.push_back(new Nbzombie);
            		contofnbzombies = 0;
        	}
}

int main() {
	initgraph(1280,960,EX_SHOWCONSOLE);
	mciSendString("play res/Faster.mp3 repeat",NULL, 0, NULL);

	Map map;
	Player player;
	Enemy enemy;
	vector < Orzbie *>orzbies_lists; 
	vector < Bullet *>fierbullet_lists;
	vector < Nbzombie*>nbzombie_lists;
	Control control(&map, &player);
	control.init();
	Bullet test(&player);
	
	while (1)
	{
		gametime = clock();
		clock_t starttime = clock();//记录开始时间
		if (gametime <= 60000) {
			stage = 1;
		}
		else if (gametime >60000 && gametime <= 120000)
		{
			stage = 2;
		}
		else if (gametime > 120000 && gametime <= 180000) {
			stage = 3;
		}
		if (stage == 1) //僵尸第一阶段
		{
			BeginBatchDraw();
			cleardevice();
			map.init();
			player.move();
			getozombies(orzbies_lists);
			for (int i = 0; i < orzbies_lists.size(); i++)
			{
				orzbies_lists[i]->move();
			}
			getfierbullet(fierbullet_lists, &player);
			for (int i = 0; i < fierbullet_lists.size(); i++)
			{
				fierbullet_lists[i]->move();
			}
			control.drawHP();
			control.shouscore();
			EndBatchDraw();
			control.checkoutorzbies(orzbies_lists, fierbullet_lists);
			control.contactorzbies(orzbies_lists, fierbullet_lists);
		}
		if (stage == 2)//僵尸第二阶段
		{
			BeginBatchDraw();
			cleardevice();
			map.init();
			player.move();
			getnbzombie(nbzombie_lists);
			for (int i = 0; i < nbzombie_lists.size(); i++)
			{
				nbzombie_lists[i]->move();
			}
			getfierbullet(fierbullet_lists, &player);
			for (int i = 0; i < fierbullet_lists.size(); i++)
			{
				fierbullet_lists[i]->move();
			}
			control.drawHP();
			control.shouscore();
			EndBatchDraw();
			control.checkoutnbzombies(nbzombie_lists, fierbullet_lists);
			control.contactnbzombies(nbzombie_lists, fierbullet_lists);
		
		}
		clock_t endtime = clock();//记录结束时间
		if (endtime - starttime < 1000 / gameframerate) {
	    //cout << "帧率为：" << gameframerate;
			Sleep(1000 / gameframerate - (endtime - starttime));
		}//	控制帧率	
	}
	return 0;
}