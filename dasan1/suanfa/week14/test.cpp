#include <iostream>
using namespace std;



class hero {
private:
    enum heroAttrType {
        attk, def, hp, mp
    };
    struct heroAttr {
        char const* name;
        int attk;
        int def;
        int hp;
        int mp;
        heroAttr* next;
    };
    int len = 0;
    heroAttr* heroattr = nullptr;
    heroAttr* hero = nullptr;
    


public:
    void Add(const char* name, int attk, int def, int hp, int mp);
    void Print();
};

void hero::Add(const char* _name, int _attk, int _def, int _hp, int _mp) {
    if(len == 0)
    {
        heroAttr newHero;
        newHero.name = _name;
        // // newHero.attk = _attk;
        // // newHero.def = _def;
        // // newHero.hp = _hp;
        // // newHero.mp = _mp;
        // heroattr[0] = newHero;
        newHero.next = new heroAttr;
        newHero.next = nullptr;
        heroattr = &newHero;
        hero = heroattr;
    } else {
        heroAttr newHero;
        newHero.name = _name;
        newHero.next = new heroAttr;
        heroattr->next = &newHero;
    }
    len = len+1;

    

    return; 
}

void hero::Print() {
    cout << hero->name << endl;
    hero = hero->next;
    cout << hero->name << endl;
    // cout << heroattr[1].name << endl;
    // cout << heroattr[len].attk << endl;
    // cout << heroattr[len].def << endl;
    // cout << heroattr[len].hp << endl;
    // cout << heroattr[len].mp << endl;
}

struct heroAttr {
    char const* name;
    int attk;
    int def;
    int hp;
    int mp;
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
    hero myhero;
    myhero.Add("xiang", 1000, 2000, 100, 200);
    myhero.Add("123", 1000, 2000, 100, 200);
    myhero.Print();

    return 0;
}