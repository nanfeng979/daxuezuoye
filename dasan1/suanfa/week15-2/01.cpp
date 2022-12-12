#include<iostream>
using namespace std;

void payBack(int yuan, int jiao)
{
    int count = 0; //定义整数变量count，表示找现金的货币数量
    while (yuan >= 5) //当需要找的现金的元部分大于等于5元时
    {
        yuan -= 5; //减去5元
        count++; //货币数量加1
        cout << "找了1张5元的货币。" << endl; //输出
    }
    while (yuan >= 2) //当需要找的现金的元部分大于等于2元时
    {
        yuan -= 2; //减去2元
        count++; //货币数量加1
        cout << "找了1张2元的货币。" << endl; //输出
    }
    while (yuan >= 1) //当需要找的现金的元部分大于等于1元时
    {
        yuan -= 1; //减去1元
        count++; //货币数量加1
        cout << "找了1张1元的货币。" << endl; //输出
    }
    while (jiao >= 5) //当需要找的现金的角部分大于等于5角时
    {
        jiao -= 5; //减去5角
        count++; //货币数量加1
        cout << "找了1张5角的货币。" << endl; //输出
    }
    while (jiao >= 2) //当需要找的现金的角部分大于等于2角时
    {
        jiao -= 2; //减去2角
        count++; //货币数量加1
        cout << "找了1张2角的货币。" << endl; //输出
    }
    while (jiao >= 1) //当需要找的现金的角部分大于等于1角时
    {
        jiao -= 1; //减去1角
        count++; //货币数量加1
        cout << "找了1张1角的货币。" << endl; //输出
    }
}

int main()
{
    payBack(4, 6);
}