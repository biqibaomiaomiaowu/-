#include "Bullet.h"

Bullet::Bullet(Player * player)
{
	this->player = player;
    if (player->getskill_bigbullet()) {
        skill_bigbullet = true;
        ATK *=2;
    }
    char name[50] = { 0 };
        for (int i = 0; i < 2; i++) {
            sprintf_s(name, "res/fierbullet(%d).png", i+1);
    
           loadimage(&bullet[i], name);
           loadimage(&bigbullet[i], name, 84, 46);
        }
        x = player->getx() + 194;
        y = player->gety() + 128;
}


void Bullet::putimagePNG(int x, int y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{
    // 变量初始化
    DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
    DWORD* draw = GetImageBuffer();
    DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
    int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
    int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
    int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
    int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
    int dstX = 0;    //在显存里像素的角标

    // 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
    for (int iy = 0; iy < picture_height; iy++)
    {
        for (int ix = 0; ix < picture_width; ix++)
        {
            int srcX = ix + iy * picture_width; //在显存里像素的角标
            int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
            int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
            int sg = ((src[srcX] & 0xff00) >> 8);   //G
            int sb = src[srcX] & 0xff;              //B
            if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
            {
                dstX = (ix + x) + (iy + y) * graphWidth; //在显存里像素的角标
                int dr = ((dst[dstX] & 0xff0000) >> 16);
                int dg = ((dst[dstX] & 0xff00) >> 8);
                int db = dst[dstX] & 0xff;
                draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
                    | ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
                    | (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
            }
        }
    }
}
int Bullet::getx()
{
    return x;
}
int Bullet::gety()
{
    return y;
}

int Bullet::getATK()
{
    return ATK;
}

void Bullet::skill_trace_orzbie_bullet(std::vector < Orzbie*>& orzbies_lists)
{
    draw();
    gamecont++;
    if (gamecont == playframerate) {
        imagenub++;
        gamecont = 0;
    }
    imagenub %= 2;
    int distance_x= orzbies_lists[0]->getx()+10-x;

    int distance_y = orzbies_lists[0]->gety()+100 - y;

    double distance = sqrt(distance_x * distance_x + distance_y * distance_y);
    double cos = distance_x / distance;
    double sin = distance_y / distance;
    x += cos * speed;
    y += sin * speed;

}

void Bullet::skill_trace_nbzombie_bullet(std::vector<Nbzombie*> nbzombie_lists)
{
    draw();
    gamecont++;
    if (gamecont == playframerate) {
        imagenub++;
        gamecont = 0;
    }
    imagenub %= 2;
    int distance_x = nbzombie_lists[0]->getx() + 10 - x;

    int distance_y = nbzombie_lists[0]->gety() + 100 - y;

    double distance = sqrt(distance_x * distance_x + distance_y * distance_y);
    double cos = distance_x / distance;
    double sin = distance_y / distance;
    x += cos * speed;
    y += sin * speed;

}




void Bullet::draw()
{
    if (!skill_bigbullet) {
        putimagePNG(x, y, &bullet[imagenub]);

    }
    else {
        putimagePNG(x, y, &bigbullet[imagenub]);
    }
    
}

void Bullet::move()
{

    draw();
    gamecont++;
    if (gamecont == playframerate) {
        imagenub++;
        gamecont = 0;
    }
    imagenub %= 2;
    x += speed;
    
}

