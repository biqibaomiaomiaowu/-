#include "Nbzombie.h"

Nbzombie::Nbzombie()
{
    
        char name[50] = { 0 };
        int nub = 1;

        for (int i = 0; i < 55; i++) {
            sprintf_s(name, "res/nbzombie (%d).png", nub);
            loadimage(&nbzombies[i], name, 200, 230);
            nub++;
        }
        zombieposition();
    
}

void Nbzombie::move()
{
    x -= speed;
    draw();
    gamecont++;
    if (gamecont == playframerate) {
        gamecont = 0;
        imagenub++;
    }
    imagenub %= 54;
}

void Nbzombie::draw()
{
    putimagePNG(x, y, &nbzombies[imagenub]);
}

void Nbzombie::putimagePNG(int x, int y, IMAGE* picture)
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

void Nbzombie::zombieposition()
{
    // 创建随机设备（硬件熵源）
        std::random_device rd;

    // 使用 Mersenne Twister 算法（高性能随机数生成器）
    std::mt19937 gen(rd());

    // 定义均匀整数分布范围 [0, 730]（闭区间）
    std::uniform_int_distribution<int> dist(0, 730);

    // 生成并输出随机数
    int random_number = dist(gen);
    y = random_number;//随机出生位置
    imagenub = random_number % 10;//让每个orzbie的动作不一样
}

int Nbzombie::getx()
{
    return x;
}

int Nbzombie::gety()
{
    return y;
}

void Nbzombie::getattack()
{
    HP--;
}

int Nbzombie::getHP()
{
    return HP;
}
