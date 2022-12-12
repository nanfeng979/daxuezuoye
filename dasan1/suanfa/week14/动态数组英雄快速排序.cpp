#include <iostream>
#include <string>
using namespace std;

struct Hero{
	string Name;
	int HP; // ����ֵ 
	int DV; // ����ֵ
	int OC; // ������
	int MV; // ħ��ֵ 
}; 
enum Type 
{
	name,
	
};

class HeroArray {
private: 
	Hero* Heros = nullptr; // �����Ա 
public:
	int Length = 0; // ���鳤��  
public:
	HeroArray()
	{
		cout << "���鴴�����" << endl;
	}
	void Add(string Name, int HP, int DV, int OC, int MV)
	{
		Hero newHero;
		newHero.Name = Name;
		newHero.HP = HP;
		newHero.DV = DV;
		newHero.OC = OC;
		newHero.MV = MV;
		
		if(this->Length == 0)
		{
			this->Heros = new Hero[1];
			this->Heros[0] = newHero;
			this->Length++;
			return; 
		}
		
		int newLength = ++this->Length;
		Hero* newHeros = new Hero[newLength];
		for(int i = 0; i < this->Length - 1; i++)
		{
			newHeros[i] = this->Heros[i]; 
			delete &this->Heros[i]; 
		} 
		newHeros[this->Length - 1] = newHero;
		delete this->Heros;
		this->Heros = newHeros;
	} 
	void List()
	{
		for(int i = 0; i < this->Length; i++)
			cout << this->Heros[i].Name << endl;
	} 
	
	void QuickSort(int L, int R)
	{
		if(L >= R) return;
		int left = L;
		int right = R;
		Hero pivot = this->Heros[left];
		while(left < right) 
		{
			while(left < right)
			{
				if(this->Heros[right].HP >= pivot.HP)
				{
					right--;
				}
				else
				{
					this->Heros[left] = this->Heros[right];
					break;
				}
			}
			while(left < right)
			{
				if(this->Heros[left].HP <= pivot.HP)
				{
					left++;
				}
				else
				{
					this->Heros[right] = this->Heros[left];
					break; 
				} 
			}
			if(left >= right)
			{
				this->Heros[left] = pivot;
			}
		} 
		this->QuickSort(L, right - 1);
		this->QuickSort(right + 1, R);
	} 
};

int main()
{
	HeroArray* heros = new HeroArray();
	heros->Add("hah", 200, 24, 32, 41);
	heros->Add("haixin", 120, 22, 33, 42);
	heros->Add("���а�", 130, 21, 37, 43);
	heros->List();
	heros->QuickSort(0, 2);
		heros->List();
	 
	return 0;
}
