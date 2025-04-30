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

void getozombies(vector < Orzbie*> &orzbies_lists, int bulletATK)
{
	contofozombies++;
	if (contofozombies >= rateofozombies) 
	{
		orzbies_lists.push_back(new Orzbie(bulletATK));
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
void getnbzombie(vector < Nbzombie*>&nbzombie_lists,int bulletATK)
{
    	contofnbzombies++;
        	if (contofnbzombies >= rateofnbzombies) {
            		nbzombie_lists.push_back(new Nbzombie(bulletATK));
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
	
	bool skillchooseone = false;
	
	while (1)
	{
		Bullet test(&player);
		int bulletATK = test.getATK();
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
			getozombies(orzbies_lists,bulletATK);
			for (int i = 0; i < orzbies_lists.size(); i++)
			{
				orzbies_lists[i]->move();
			}
			getfierbullet(fierbullet_lists, &player);
			for (int i = 0; i < fierbullet_lists.size(); i++)
			{
				if (!player.getskill_tracebullet()) {
					
					fierbullet_lists[i]->move();

				}
				else {
					if (orzbies_lists.size() == 0) {
						fierbullet_lists[i]->move();
					}
					else {
						fierbullet_lists[i]->skill_trace_orzbie_bullet(orzbies_lists);

					}
				}
			}
			control.drawHP();
			control.shouscore();
			if (player.getskill_circlebullet()) 
			{
				control.drawcirclebullet();

			}
			
			if (control.getscore() >= 3&&!skillchooseone) 
			{ 
				control.showskill();
				EndBatchDraw();
				ExMessage msg;
				while (1) 
				{
					while (peekmessage(&msg, EX_MOUSE)) {
						if (msg.message == WM_LBUTTONDOWN) {
							if (msg.x >= 400 && msg.x <= 450&& msg.y >= 300 && msg.y <= 350)
							{
								player.changeskill_tracebullet();
								skillchooseone = true;
							}
							if (msg.x >= 470 && msg.x <= 520 && msg.y >= 300 && msg.y <= 350)
							{
								player.changeskill_bigbullet();
								
								skillchooseone = true;
							}
							if (msg.x >= 540 && msg.x <= 590 && msg.y >= 300 && msg.y <= 350) 
							{
								player.changeskill_circlebullet();
								skillchooseone = true;
							}

						}
					}
					if (skillchooseone) {
                        break;
					}
				}
			}
			EndBatchDraw();
			control.checkoutorzbies(orzbies_lists, fierbullet_lists);
			control.contactorzbies(orzbies_lists, fierbullet_lists);
			control.contactcirclebullet(nbzombie_lists, orzbies_lists);
		}
		if (stage == 2)//僵尸第二阶段
		{
			BeginBatchDraw();
			cleardevice();
			map.init();
			player.move();
			for (int i = 0; i < orzbies_lists.size(); i++)
			{
				orzbies_lists[i]->move();
			}


			getnbzombie(nbzombie_lists,bulletATK);
			for (int i = 0; i < nbzombie_lists.size(); i++)
			{
				nbzombie_lists[i]->move();
			}
			getfierbullet(fierbullet_lists, &player);
			for (int i = 0; i < fierbullet_lists.size(); i++)
			{
				if (!player.getskill_tracebullet())
				{

					fierbullet_lists[i]->move();

				}
				else 
				{
					if (nbzombie_lists.size() == 0) {
						fierbullet_lists[i]->move();
					}
					else {
						fierbullet_lists[i]->skill_trace_nbzombie_bullet(nbzombie_lists);

					}
				}
			}
			control.drawHP();
			control.shouscore();
			EndBatchDraw();
			control.checkoutorzbies(orzbies_lists, fierbullet_lists);
			control.contactorzbies(orzbies_lists, fierbullet_lists);
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