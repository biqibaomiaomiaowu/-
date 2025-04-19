#include "control.h"
void Control::init()
{
    map->init();
    player->init();

}
Control::Control(Map* map, Player* player)
{
    this->map = map;
    this->player = player;

}

void Control::checkout(std::vector<Orzbie*>& orzbies_lists, std::vector<Bullet*>& bullets_lists)
{
    for (int i = 0; i < orzbies_lists.size(); i++) {
        if (orzbies_lists[i]->getx() <0) {
            delete orzbies_lists[i];
            orzbies_lists.erase(orzbies_lists.begin() + i);
        }
    }
    for (int i = 0; i < bullets_lists.size(); i++) {
        if (bullets_lists[i]->getx() > 1200) {
            delete bullets_lists[i];
            bullets_lists.erase(bullets_lists.begin() + i);
        }
    }
}

void Control::contact(std::vector < Orzbie*>& orzbies_lists, std::vector < Bullet*>& bullets_lists)
{
    for (int i = 0; i < bullets_lists.size(); i++) {
        for (int j = 0; j < orzbies_lists.size(); j++) {
            if (bullets_lists[i]->getx() + 28 > orzbies_lists[j]->getx()
                && bullets_lists[i]->getx() + 28 < orzbies_lists[j]->getx() + 170
                && bullets_lists[i]->gety() + 17 > orzbies_lists[j]->gety()
                && bullets_lists[i]->gety() + 17 < orzbies_lists[j]->gety() + 200) 
            {
                delete bullets_lists[i];
                bullets_lists.erase(bullets_lists.begin() + i);
                delete orzbies_lists[j];
                orzbies_lists.erase(orzbies_lists.begin() + j);

            }

        }

        
   }
}
