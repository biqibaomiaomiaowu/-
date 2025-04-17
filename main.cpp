#include<iostream>
#include"control.h"
#include<time.h>
#include"Orzbie.h"
#include<vector>
using namespace std;
int gameframerate = 60;
int contofozombies = 0;
int rateofozombies = 100;
void getozombies(vector < Orzbie*> &orzbies_lists) {
	contofozombies++;
	if (contofozombies >= rateofozombies) {
		orzbies_lists.push_back(new Orzbie());
		contofozombies = 0;
	}
}
int main() {
	initgraph(1280,960,EX_SHOWCONSOLE);
	Map map;
	Player player;
	Enemy enemy;
	vector < Orzbie *>orzbies_lists; 
	Control control(&map, &player);
	control.init();

	
	while (1)
	{
		clock_t starttime = clock();//记录开始时间

		BeginBatchDraw();
		cleardevice();
		map.init();
		player.move();
		getozombies(orzbies_lists);
		for (int i = 0; i < orzbies_lists.size(); i++) {
            			orzbies_lists[i]->move();
		}
		EndBatchDraw();
		clock_t endtime = clock();//记录结束时间
		if (endtime - starttime < 1000 / gameframerate) {
	    //cout << "帧率为：" << gameframerate;
			Sleep(1000 / gameframerate - (endtime - starttime));
		}//	控制帧率	
	}
	return 0;
}