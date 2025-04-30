#include "control.h"
void Control::init()
{
    loadimage(&brain, "res/brian.png", 0, 0);
    loadimage(&skill_tracebullet, "res/tracebullet.png", 50,50);
    loadimage(&skill_bigbullet,"res/fierbullet(1).png",50,50);
    loadimage(&skill_circlebullet, "res/红色光环_爱给网_aigei_com.png", 50, 50);

    map->init();
    player->init();

}
Control::Control(Map* map, Player* player)
{
    this->map = map;
    this->player = player;

}

void Control::checkoutorzbies(std::vector<Orzbie*>& orzbies_lists, std::vector<Bullet*>& bullets_lists)
{
    for (int i = 0; i < orzbies_lists.size(); i++) {
        if (orzbies_lists[i]->getx() <0) {
            delete orzbies_lists[i];
            orzbies_lists.erase(orzbies_lists.begin() + i);
            HP--;
            mciSendString("play res/chomp.mp3", NULL, 0, NULL);
            if (HP == 0) {
                settextcolor(RED);
                settextstyle(300,500,0);
                setbkmode(TRANSPARENT);
                outtextxy(500, 500, "Game Over");
                mciSendString("stop res/Faster.mp3", NULL, 0, NULL);
                mciSendString("play res/losemusic.mp3", NULL, 0, NULL);
                Sleep(7000);
            }
        }
    }
    for (int i = bullets_lists.size()-1; i >= 0; i--) {
        if (bullets_lists[i]->getx() > 1200) {
            delete bullets_lists[i];
            bullets_lists.erase(bullets_lists.begin() + i);
        }
    }
}

void Control::contactorzbies(std::vector < Orzbie*>& orzbies_lists, std::vector < Bullet*>& bullets_lists)
{
    for (int i = bullets_lists.size() - 1; i >= 0; --i) {
        for (int j = orzbies_lists.size() - 1; j >= 0; --j) {
            if (bullets_lists[i]->getx() + 28 > orzbies_lists[j]->getx()
                && bullets_lists[i]->getx() + 28 < orzbies_lists[j]->getx() + 170
                && bullets_lists[i]->gety() + 17 > orzbies_lists[j]->gety()
                && bullets_lists[i]->gety() + 17 < orzbies_lists[j]->gety() + 200) 
            {
                if (playbulletsound1 == false) {
                    mciSendString("play res/splat1.mp3", 0, 0, 0);
                    playbulletsound1 = true;
                    std::cout << "1";
                }
                else {
                    mciSendString("play res/splat2.mp3", 0, 0, 0);
                    playbulletsound1 = false;
                    std::cout << "2";
                }
                
                orzbies_lists[j]->getattack();
                if (orzbies_lists[j]->getHP() <= 0) {
                    delete orzbies_lists[j];
                    orzbies_lists[j] = NULL;
                    orzbies_lists.erase(orzbies_lists.begin() + j);
                    score++;
                }
                delete bullets_lists[i];
                bullets_lists[i] = NULL;
                bullets_lists.erase(bullets_lists.begin() + i);
                
               
                
                break;

                
                

            }

        }

        
   }
}


void Control::drawHP()
{
    
    if (HP == 3) {
        putimagePNG(0, 0, &brain);
        putimagePNG(70, 0, &brain);
        putimagePNG(140, 0, &brain);

    }
    else if (HP == 2) {
        putimagePNG(0, 0, &brain);
        putimagePNG(70, 0, &brain);
    }
    else if (HP == 1) {
        putimagePNG(0, 0, &brain);
    }
}

void Control::putimagePNG(int x, int y, IMAGE* picture)
{  // 变量初始化
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

void Control::shouscore() {
    settextcolor(RED);
    settextstyle(50, 0, 0);
    setbkmode(TRANSPARENT);
    char score1[50] = { 0 };
    sprintf_s(score1, "score::%d", score);
    outtextxy(200, 0, score1);


}

int Control::getscore()
{
    return score;
}

void Control::checkoutnbzombies(std::vector<Nbzombie*>& nbzombie_lists, std::vector<Bullet*>& bullets_lists)
{
    for (int i = 0; i < nbzombie_lists.size(); i++) {
        if (nbzombie_lists[i]->getx() < 0) {
            delete nbzombie_lists[i];
            nbzombie_lists.erase(nbzombie_lists.begin() + i);
            HP--;
            mciSendString("play res/chomp.mp3", NULL, 0, NULL);
            if (HP == 0) {
                settextcolor(RED);
                settextstyle(300, 500, 0);
                setbkmode(TRANSPARENT);
                outtextxy(500, 500, "Game Over");
                mciSendString("stop res/Faster.mp3", NULL, 0, NULL);
                mciSendString("play res/losemusic.mp3", NULL, 0, NULL);
                Sleep(7000);
            }
        }
    }
    for (int i = bullets_lists.size()-1; i >=0; i--) {
        if (bullets_lists[i]->getx() > 1200) {
            delete bullets_lists[i];
            bullets_lists.erase(bullets_lists.begin() + i);
        }
    }

}

void Control::contactnbzombies(std::vector<Nbzombie*>& nbzombie_lists, std::vector<Bullet*>& bullets_lists)
{
    for (int i = bullets_lists.size() - 1; i >= 0; --i) {
        for (int j = nbzombie_lists.size() - 1; j >= 0; --j) {
            if (bullets_lists[i]->getx() + 28 > nbzombie_lists[j]->getx()
                && bullets_lists[i]->getx() + 28 < nbzombie_lists[j]->getx() + 170
                && bullets_lists[i]->gety() + 17 > nbzombie_lists[j]->gety()
                && bullets_lists[i]->gety() + 17 < nbzombie_lists[j]->gety() + 200)
            {
                if (playbulletsound1 == false) {
                    mciSendString("play res/splat1.mp3", 0, 0, 0);
                    playbulletsound1 = true;
                    std::cout << "1";
                }
                else {
                    mciSendString("play res/splat2.mp3", 0, 0, 0);
                    playbulletsound1 = false;
                    std::cout << "2";
                }

                nbzombie_lists[j]->getattack();
                if (nbzombie_lists[j]->getHP() == 0) {
                    delete nbzombie_lists[j];
                    nbzombie_lists[j] = NULL;
                    nbzombie_lists.erase(nbzombie_lists.begin() + j);
                    score++;
                }
                delete bullets_lists[i];
                bullets_lists[i] = NULL;
                bullets_lists.erase(bullets_lists.begin() + i);



                break;




            }

        }


    }
}

void Control::showskill()
{
    putimagePNG(400, 300, &skill_tracebullet);
    putimagePNG(470, 300, &skill_bigbullet);
    putimagePNG(540, 300, &skill_circlebullet);
}

void Control::drawcirclebullet()
{
    double Ve = 0.0045;
    double Vn= 0.0045;
    int time = clock();
    int r = 200+50*cos(Vn*time);
    setfillcolor(RED);
    int x = player->getx() + 133;
    int y = player->gety() + 120;
    double distance = 2 * 3.1415926 / 3;
    for (int i = 0; i < 3; i++) 
    {
        
        fillcircle(x + r *cos(distance*i+Ve*time), y + r * sin(distance * i + Ve * time), 10);
        circlebullet[i][0] = x + r * cos(distance * i + Ve * time);
        circlebullet[i][1] = y + r * sin(distance * i + Ve * time);
    }
}

void Control::contactcirclebullet(std::vector<Nbzombie*>& nbzombie_lists, std::vector<Orzbie*>& orzbies_lists)
{
    
    circlebulletcoolcont++;
    circlebulletcoolcont %= 15;
    for (int i = 0; i < 3; i++) {
        for (int j = nbzombie_lists.size() - 1; j >= 0; --j) 
        {
            if (circlebullet[i][0] > nbzombie_lists[j]->getx()
                && circlebullet[i][0] < nbzombie_lists[j]->getx() + 170
                && circlebullet[i][1] > nbzombie_lists[j]->gety()
                && circlebullet[i][1] < nbzombie_lists[j]->gety() + 200&&circlebulletcoolcont==0) 
            {
                nbzombie_lists[j]->HPdown();
                mciSendString("play res/厨刀切割声-日常厨房-食材处理音效_爱给网_aigei_com.mp3", NULL, 0, NULL);
            }
            if (nbzombie_lists[j]->getHP() == 0) {
                delete nbzombie_lists[j];
                nbzombie_lists[j] = NULL;
                nbzombie_lists.erase(nbzombie_lists.begin() + j);
                score++;
            }
        
        }
        for (int j = orzbies_lists.size() - 1; j >= 0; --j)
        {
            if (circlebullet[i][0] > orzbies_lists[j]->getx()
                && circlebullet[i][0] < orzbies_lists[j]->getx() + 170
                && circlebullet[i][1] > orzbies_lists[j]->gety()
                && circlebullet[i][1] < orzbies_lists[j]->gety() + 200 && circlebulletcoolcont == 0)
            {
                orzbies_lists[j]->HPdown();
                mciSendString("play res/厨刀切割声-日常厨房-食材处理音效_爱给网_aigei_com.mp3", NULL, 0, NULL);
            }
            if (orzbies_lists[j]->getHP() == 0) {
                delete orzbies_lists[j];
                orzbies_lists[j] = NULL;
                orzbies_lists.erase(orzbies_lists.begin() + j);
                score++;
            }

        }
    }
}
