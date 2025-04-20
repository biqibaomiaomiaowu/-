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

int main() {
	initgraph(1280,960,EX_SHOWCONSOLE);
	mciSendString("play res/Faster.mp3 repeat",NULL, 0, NULL);

	Map map;
	Player player;
	Enemy enemy;
	vector < Orzbie *>orzbies_lists; 
	vector < Bullet *>fierbullet_lists;
	Control control(&map, &player);
	control.init();
	Bullet test(&player);
	
	while (1)
	{
		clock_t starttime = clock();//记录开始时间

		BeginBatchDraw();
		cleardevice();
		map.init();
		player.move();
		getozombies(orzbies_lists);
		for (int i = 0; i < orzbies_lists.size(); i++) 
		{
            			orzbies_lists[i]->move();
		}
		getfierbullet(fierbullet_lists,&player);
		for (int i = 0; i < fierbullet_lists.size(); i++) 
		{
			fierbullet_lists[i]->move();
		}
		
		EndBatchDraw();
		control.checkout(orzbies_lists, fierbullet_lists);
		control.contact(orzbies_lists,fierbullet_lists);
		clock_t endtime = clock();//记录结束时间
		if (endtime - starttime < 1000 / gameframerate) {
	    //cout << "帧率为：" << gameframerate;
			Sleep(1000 / gameframerate - (endtime - starttime));
		}//	控制帧率	
	}
	return 0;
}