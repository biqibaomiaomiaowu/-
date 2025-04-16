#include<iostream>
#include"control.h"
#include<time.h>
using namespace std;
int main() {
	initgraph(1280,960,EX_SHOWCONSOLE);
	Map map;
	Player player;
	Enemy enemy;
	Control control(&map, &player, &enemy);
	control.init();
	while (1)
	{
		clock_t starttime = clock();//记录开始时间
		BeginBatchDraw();
		cleardevice();
		map.init();
		player.move();
		EndBatchDraw();
		clock_t endtime = clock();//记录结束时间
		if (endtime - starttime < 1000 / 60) {
			Sleep(1000 / 60 - (endtime - starttime));
		}//	控制帧率	
	}
	getchar();
	return 0;
}