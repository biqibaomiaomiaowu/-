#include<iostream>
#include"control.h"
using namespace std;
int main() {
	initgraph(1280,960,EX_SHOWCONSOLE);
	Map map;
	Player player;
	Enemy enemy;
	Control control(&map, &player, &enemy);
	control.init();
	getchar();
	return 0;
}