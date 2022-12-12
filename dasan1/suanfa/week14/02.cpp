#include <iostream>
using namespace std;

struct heroAttr {
    char const* name;
    int attk;
    int def;
    int hp;
    int mp;
    heroAttr(){
        this->name = "null";
        this->attk = 0;
        this->def = 0;
        this->hp = 0;
        this->mp = 0;
    };
    heroAttr(char const* name,
    int attk,
    int def,
    int hp,
    int mp){
        this->name = name;
        this->attk = attk;
        this->def = def;
        this->hp = hp;
        this->mp = mp;
    };
};

struct allHero {
    heroAttr hero[3];
    int len;
};

enum heroAttrType {
    attk, def, hp, mp
};

int part(heroAttr *v, int low, int height, heroAttrType sortType)
{
    int i = low, j = height, key;
    switch(sortType)
    {
        case attk:
            key = v[low].attk;
            break;
        case def:
            key = v[low].def;
            break;
        case hp:
            key = v[low].hp;
            break;
        case mp:
            key = v[low].mp;
            break;
    }

    while(i < j)
    {
        while(i < j && v[j].attk > key)
        {
            j--;
        }
        if(i < j)
        {
            auto temp = v[i];
            v[i] = v[j];
            v[j] = temp;
            i++;
        }

        while(i < j && v[i].attk <= key)
        {
            i++;
        }
        if(i < j)
        {
            auto temp = v[i];
            v[i] = v[j];
            v[j] = temp;
            j--;
        }
    }

    return i;
}

void Quicksort(heroAttr *v, int low, int height, heroAttrType heroattrtype)
{
    int mid;
    if(low < height)
    {
        mid = part(v, low, height, heroattrtype);
        Quicksort(v, low, mid - 1, heroattrtype);
        Quicksort(v, mid + 1, height, heroattrtype);
    }
}

int main()
{
    allHero heros;
    heros.len = 3;
    
    heros.hero[0] = {"Blue Eyed White Dragon", 3000, 2500, 8000, 4};
    heros.hero[1] = {"Black Magician", 2500, 2100, 4000, 5};
    heros.hero[2] = {"DDD twin king Cali Yuga", 3500, 3000, 2000, 6};

    Quicksort(heros.hero, 0, heros.len, attk);

    cout << "升序排序：" << endl;
    for(int i = 0; i < heros.len; i++)
    {
        cout << "No." << i + 1 << ": ";
        cout << heros.hero[i].name << endl;
        cout << heros.hero[i].attk << "  ";
        cout << heros.hero[i].def << endl;
        cout << heros.hero[i].hp << "  ";
        cout << heros.hero[i].mp << endl;
    }
    return 0;
}